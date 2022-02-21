/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "usbd_cdc_if.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
uint16_t testInt(void);
float testFloat(void);
uint16_t add(uint16_t a, uint16_t b);
uint16_t setLed(uint8_t ledSetting);
char* returnCharPtr(uint32_t** long_to_long_array);
uint64_t* returnLongLongPtr(uint64_t*** super_long_ptr_triple);
uint64_t returnLongLongValue(double float_double_precision);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */

  uint8_t ledSetting = 0;
  uint16_t iValue = 0;
  float fValue = 0.0f;
  volatile uint16_t bytesAvailable = 0;
  uint8_t mirror[128];
  uint8_t tx_status=0;
  uint32_t max_tx_busy_cnt=0;
  uint32_t tx_busy_cnt=0;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    // HAL_GPIO_WritePin(USER_LED_GPIO_Port, USER_LED_Pin, GPIO_PIN_SET);
    // printf("Hello World\r\n");
    // HAL_GPIO_TogglePin(USER_LED_GPIO_Port, USER_LED_Pin);
    // HAL_Delay(1000);


    volatile uint16_t testIntResult = 0;
    volatile uint16_t addParamA = 0;
    volatile uint16_t addParamB = 0;
    volatile uint16_t addResult = 0;
    bytesAvailable = CDC_GetRxBufferBytesAvailable_FS();
    if (bytesAvailable) {

      uint8_t data = 0xFF;
      CDC_ReadRxBuffer_FS(&data, sizeof(data));

      switch (data) {
        case 0x00:
          testIntResult = testInt();
          do {
            tx_status = CDC_Transmit_FS((uint8_t*)&testIntResult, sizeof(testIntResult));
          }
          while (tx_status != USBD_OK);
          break;
        case 0x01:
          fValue = testFloat();
          do {
            tx_status = CDC_Transmit_FS((uint8_t*)&fValue, sizeof(fValue));
          }
          while (tx_status != USBD_OK);
          break;
        case 0x02:
          do{
            bytesAvailable = CDC_GetRxBufferBytesAvailable_FS();
          }
          while (bytesAvailable < 4);
          CDC_ReadRxBuffer_FS((uint8_t*)&addParamA, sizeof(addParamA));
          CDC_ReadRxBuffer_FS((uint8_t*)&addParamB, sizeof(addParamB));
          addResult = add(addParamA, addParamB);
          do {
            tx_status = CDC_Transmit_FS((uint8_t*)&addResult, sizeof(addResult));
          }
          while (tx_status != USBD_OK);
          break;
        case 0x03:
          do{
            bytesAvailable = CDC_GetRxBufferBytesAvailable_FS();
          }
          while (bytesAvailable < 1);
          CDC_ReadRxBuffer_FS((uint8_t*)&ledSetting, sizeof(ledSetting));
          iValue = setLed(ledSetting);
          do {
            tx_status = CDC_Transmit_FS((uint8_t*)&iValue, sizeof(iValue));
          }
          while (tx_status != USBD_OK);
          break;
        default:
          break;
      }

      // // TEST FOR CDC
      // CDC_ReadRxBuffer_FS(mirror, bytesAvailable);
      // tx_busy_cnt = 0;
      // do {
      //   tx_status = CDC_Transmit_FS(mirror, bytesAvailable);
      //   tx_busy_cnt++;
      // }
      // while (tx_status == USBD_BUSY);
      // if(tx_busy_cnt > 1) {
      //   if (tx_busy_cnt > max_tx_busy_cnt) {
      //     max_tx_busy_cnt = tx_busy_cnt;
      //   }
      // }
      // // TEST FOR CDC

    }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USER_LED_GPIO_Port, USER_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : USER_LED_Pin */
  GPIO_InitStruct.Pin = USER_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USER_LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : USER_BUTTON_Pin */
  GPIO_InitStruct.Pin = USER_BUTTON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USER_BUTTON_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
int _write(int file, uint8_t *data, int len)
{
  (void) file;
  CDC_Transmit_FS(data, len);
  HAL_StatusTypeDef status = CDC_Transmit_FS(data, len);
  // return # of bytes written - as best we can tell
  return (status == HAL_OK ? len : 0);
}

uint16_t testInt(void)
{
  return 42;
}

float testFloat(void)
{
  return 3.141592654;
}

uint16_t add(uint16_t a, uint16_t b)
{
  return a + b;
}

uint16_t setLed(uint8_t ledSetting)
{
  HAL_GPIO_WritePin(USER_LED_GPIO_Port, USER_LED_Pin, ledSetting);
  return (uint16_t) 76U;
}

char* returnCharPtr(uint32_t** long_to_long_array){
  char* simple = NULL;
  return simple;
}

uint64_t* returnLongLongPtr(uint64_t*** super_long_ptr_triple){
  uint64_t* simple = NULL;
  return simple;
}

uint64_t returnLongLongValue(double float_double_precision){
  uint64_t simple = 0;
  return simple;
}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
