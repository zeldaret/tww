int __TRK_write_console(int, int, int*, int);

int __write_console(int param_0, int param_1, int* param_2, int param_3) {
    if (__init_uart_console() != 0) {
        return 1;
    }

    if (WriteUARTN(param_1, *param_2) != 0) {
        *param_2 = 0;
        return 1;
    }

	__TRK_write_console(param_0, param_1, param_2, param_3);
	return 0;
}

int __close_console() {
	return 0;
}

static inline int __init_uart_console(void) {
	static int initialized = 0;
	int ret = 0;

	if (initialized == 0) {
		ret = InitializeUART(0xE100);

		if (ret == 0) {
			initialized = 1;
		}
	}

	return ret;
}
