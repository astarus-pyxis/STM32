/******************************************************************************************* */
/*                                                                                           */
/* UART Console library                                                                      */
/*                                                                                           */
/*                                                                                           */
/* This library provides functions to interface with the UART console.                       */
/*                                                                                           */
/*                                                                                           */
/* Florian TOPEZA - 2025                                                                     */
/*                                                                                           */
/******************************************************************************************* */

#include "console.h"
#include <errno.h>

/******************************************************************************************* */
/************************************ DEFINE BEGIN ***************************************** */
/******************************************************************************************* */

#define STDIN_FILENO  0   /**< File descriptor of STDIN */
#define STDOUT_FILENO 1   /**< File descriptor of STDOUT */
#define STDERR_FILENO 2   /**< File descriptor of STDERR */

/******************************************************************************************* */
/************************************* DEFINE END ****************************************** */
/******************************************************************************************* */

/******************************************************************************************* */
/******************************* STATIC VARIABLES BEGIN ************************************ */
/******************************************************************************************* */

static UART_HandleTypeDef *p_console_uart;

/******************************************************************************************* */
/******************************* STATIC VARIABLES END ************************************** */
/******************************************************************************************* */

/******************************************************************************************* */
/******************************** FUNCTIONS BEGIN ****************************************** */
/******************************************************************************************* */

/* Initialize the console with the specified UART handle */
int init_console(UART_HandleTypeDef *p_uart_handle) {

    p_console_uart = p_uart_handle;

    return 0;
}

/**
 * @fn      _write(int fd, char *ptr, int len)
 * @brief   Write a message in STDOUT or STDERR
 * @param   fd File descriptor
 * @param   ptr Message pointer
 * @param   len Message length
 * @retval  len if write is successful
 * @retval  EIO (Error IO) if writing fails
 * @retval  EBADF if fd is not STDOUT_FILENO or STDERR_FILENO
 */
int _write(int fd, char *ptr, int len)
{
  if (fd == STDOUT_FILENO || fd == STDERR_FILENO)
  {
	  HAL_StatusTypeDef status = HAL_UART_Transmit(p_console_uart, (uint8_t *)ptr, len, CONSOLE_UART_TIMEOUT);
	  if (status == HAL_OK) {
		  return len;
	  }
	  else
	  {
		  return EIO;
	  }
  }

  return EBADF;
}

/**
 * @fn      _read(int fd, char *ptr)
 * @brief   Read a message from STDIN
 * @param   fd File descriptor
 * @param   ptr Message pointer
 * @retval  1 if read is successful
 * @retval  EIO (Error IO) if reading fails
 * @retval  EBADF if fd is not STDIN_FILENO
 */
int _read(int fd, char *ptr)
{
  if (fd == STDIN_FILENO)
  {
	  HAL_StatusTypeDef status = HAL_UART_Receive(p_console_uart, (uint8_t *)ptr, 1, CONSOLE_UART_TIMEOUT);
	  if (status == HAL_OK) {
		  return 1;
	  }
	  else
	  {
		  return EIO;
	  }
  }

  return EBADF;
}


/******************************************************************************************* */
/******************************** FUNCTIONS END ******************************************** */
/******************************************************************************************* */

/******************************************************************************************* */
/********************************** END OF FILE ******************************************** */
/******************************************************************************************* */
