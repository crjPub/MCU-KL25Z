McuxPresso SDK为McuxPresso SDK设备的通用异步收发（UART）模块提供外围驱动程序。   
UART驱动程序包括功能API和事务API。   
功能API用于UART初始化/配置/操作，以进行优化/定制。使用功能API需要了解UART外围设备以及如何组织功能API以满足应用程序需求。所有功能API都使用外围设备基址作为第一个参数。UART功能操作组提供功能API集。  
如果事务性API的代码大小和性能能够满足要求，则可以使用事务性API快速启用外围设备，并在应用程序中启用。如果代码大小和性能是关键需求，需要参阅事务API实现并编写自定义代码。所有的事务API使用`uart_handle_t`做为第二个参数，可以通过`UART_TransferCreateHandle()`函数初始化该句柄。  
事务API支持异步传输，这意味着可以用函数`UART_TransferSendNonBlocking()`和`UART_TransferReceiveNonBlocking()`设置数据传输中断。当传输完成时，上层将通过带有`kStatus_UART_TxIdle`和`kStatus_UART_RxIdle`的回调函数得到通知。  
事务性接收API支持环缓冲区。当调用函数`UART_TransferCreateHandle()`时，将准备好缓冲区的内存并传入开始地址和大小。如果传入`NULL`那么缓冲区功能将失效。当缓冲区使能后，接收到的数据将存储在后台的缓冲区中。函数`UART_TransferReceiveNonBlocking()`首先从缓冲区获得数据。如果环形缓冲区没有足够的数据，函数首先返回环形缓冲区中的数据，然后将接收到的数据保存到用户内存中。当接收到所有数据时，上层通过`kStatus_UART_RxIdle`回调得到通知。如果接收环缓冲区已满，则通过带有`kStatus_UART_RxRingBufferOverrun`的回调通知上层。在回调函数中，上层从环缓冲区中读取数据。否则，现有数据将被新数据覆盖。  
创建句柄时指定环缓冲区大小。请注意，保留一个字节用于环缓冲区维护。

UART配置

	struct uart_config_t(uint32_t baudRate_Bps, uart_parity_mode_t parityMode, uart_stop_bit_count_t stopBitCount, bool enableTx, bool enableRx)

`baudRate_Bps`：波特率  
`parityMode`：奇偶校验，默认关闭  
`stopBitCount`：停止位数，默认为1  
`enableTx`：允许发送  
`enableRx`：允许接收  

	struct uart_transfer_t(uint8_t* data, size_t dataSize)
`data`：要传输的数据缓冲区。  
`dataSize`要传输的字节计数。  

获取默认配置

	void UART_GetDefaultConfig(uart_config_t* config)

`config`：指向用户定义的配置结构的指针。  
此函数将UART配置结构初始化为默认值。默认值如下：

	uartConfig->baudRate_Bps = 115200U; 
	uartConfig->bitCountPerChar = kUART_8BitsPerChar; 
	uartConfig->parityMode = kUART_ParityDisabled; 
	uartConfig->stopBitCount = kUART_OneStopBit; 
	uartConfig->txFifoWatermark = 0; 
	uartConfig->rxFifoWatermark = 1; 
	uartConfig->enableTx = false; 
	uartConfig->enableRx = false;

示例：

	uart_config_t user_config;
	UART_GetDefaultConfig(&user_config);

初始化  

	status_t UART_Init(UART_Type* base, const uart_config_t* config, uint32_t srcClock_Hz)

`base`：UART外围设备基址。  
`config`：指向用户定义的配置结构的指针。  
`srcClock_Hz`：UART时钟源频率，单位为赫兹。  
此功能使用用户定义的设置配置UART模块。用户可以配置配置结构，也可以使用`uart_GetDefaultConfig()`函数获取默认配置。

示例：

	uart_config_t uartConfig;
	uartConfig.baudRate_Bps = 115200U;
	uartConfig.parityMode = kUART_ParityDisabled;
	uartConfig.stopBitCount = kUART_OneStopBit;
	uartConfig.txFifoWatermark = 0;
	uartConfig.rxFifoWatermark = 1;
	UART_Init(UART1, &uartConfig, 20000000U);


获取状态

	uint32_t UART_GetStatusFlags(UART_Type* base)
此函数获取所有UART状态标志。标志返回为逻辑或枚举类型`_uart_flags`。要检查特定状态，请将返回值与枚举类型`_uart_flags`比较。比如判断标志位`kUART_TxDataRegEmptyFlag`可以使用`kUART_TxDataRegEmptyFlag & UART_GetStatusFlags(UART1)`判断。

清除状态

	status_t UART_ClearStatusFlags(UART_Type* base, uint32_t mask)

此功能使用提供的掩码清除UART状态标志。  
`mask`：要清除的状态标志；它是逻辑的或是枚举类型`_uart_flags`

读写byte数据

	static void UART_WriteByte(UART_Type* base, uint8_t data)
`data`：需要写入的数据。  
此函数直接将数据写入Tx寄存器。在调用此函数之前，上层必须确保Tx寄存器为空或Tx队列有空空间。

	static uint8_t UART_ReadByte(UART_Type* base)
此函数直接从RX寄存器读取数据。在调用此函数之前，上层必须确保RX寄存器已满或Tx队列具有数据。

读写块数据

	void UART_WriteBlocking(UART_Type* base, const uint8_t* data, size_t length)
`data`：要写入的数据的起始地址
`length`：要写入的数据的长度
此函数轮询TX寄存器，等待TX寄存器为空或等待TX FIFO有空间并将数据写入TX缓冲区。  
**注意**：此功能不检查所有数据是否发送到总线。禁用Tx之前，请检查`kUART_TransmissionCompleteFlag`以确保Tx已完成。

	
	status_t UART_ReadBlocking(UART_Type* base, uint8_t* data, size_t length)
此函数轮询RX寄存器，等待RX寄存器满或RX FIFO有数据，并从Tx寄存器读取数据。

事务初始化

	void UART_TransferCreateHandle(UART_Type* base, uart_handle_t* handle, uart_transfer_callback_t callback, void* userData)
`handle`：UART句柄指针。  
`callback`：回调函数名。  
`userData`：回调函数的参数。  
此函数初始化可用于其他UART事务API的UART句柄。通常，对于指定的UART实例，调用一次此API以获取初始化的句柄。  

缓冲区

	void UART_TransferStartRingBuffer(UART_Type* base, uart_handle_t* handle, uint8_t* ringBuffer, size_t 	ringBufferSize)
`ringBuffer`：用于后台接收的环缓冲区的起始地址。传递空值以禁用环缓冲区。
`ringBufferSize`：缓冲区大小
此函数将RX环缓冲区设置为特定的UART句柄。当使用RX环缓冲区时，即使用户不调用函数`UART_TransferReceiveNonBlocking()`，接收到的数据也存储在环缓冲区中。如果已经在环缓冲区中接收到数据，则用户可以直接从环缓冲区获取接收到的数据。
**注意**：使用RX环缓冲时，保留一个字节供内部使用。换句话说，如果`ringBufferSize`为32，则仅使用31个字节来保存数据。  

	void UART_TransferStopRingBuffer(UART_Type* base, uart_handle_t* handle)

此函数中止后台传输并卸载环缓冲区。


	status_t UART_TransferSendNonBlocking(UART_Type* base, uart_handle_t* handle, uart_transfer_t* xfer)
`xfer`：UART传输结构`uart_transfer_t`
此函数使用中断方法发送数据。这是一个非阻塞函数，它直接返回，而不等待将所有数据写入Tx寄存器。当所有数据写入ISR中的Tx寄存器时，UART驱动程序调用回调函数，并将`kStatus_UART_TxIdle`作为状态参数传递。  
**注意**：当所有数据写入TX寄存器时，`kStatus_UART_TxIdle`被传递到上层。但是，它不能确保所有数据都被发送出去。禁用Tx之前，请检查`kUART_TransmissionCompleteFlag`标志以确保Tx已完成。  

	status_t UART_TransferReceiveNonBlocking(UART_Type* base, uart_handle_t* handle, uart_transfer_t* xfer, size_t* receivedBytes)
`receivedBytes`：直接从环缓冲区接收的字节。  
此函数使用中断方法接收数据。这是一个非阻塞函数，返回时不等待接收所有数据。如果使用RX环缓冲区而不是空的，则复制环缓冲区中的数据，参数`receiveDBytes`显示从环缓冲区复制的字节数。复制后，如果环缓冲区中的数据不足以读取，则由UART驱动程序保存接收请求。当新数据到达时，首先为接收请求提供服务。当接收到所有数据时，UART驱动程序通过回调函数通知上层，并传递状态参数`kStatus_UART_RxIdle`。例如，上层需要10个字节，但环缓冲区中只有5个字节。将5个字节复制到`xfer->data`，此函数返回参数`receiveDBytes`设置为5。对于左边的5个字节，新到达的数据保存在`xfer->data[5]`中。当接收到5个字节时，UART驱动程序通知上层。如果没有启用RX环缓冲器，此功能使RX和RX中断能够接收到`xfer->data`，当接收到所有数据时，会通知上层。


---
什么是DMA —- Directional Memory Access, 直接存储器存取用来提供在外设和存储器之间或者存储器和存储器之间的高速数据传输。无须CPU干预，数据可以通过DMA快速地移动，这就节省了CPU的资源来做其他操作





