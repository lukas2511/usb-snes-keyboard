#include <SNES.h>

void InitializeTimer(void)
{
        NVIC_InitTypeDef NVIC_InitStructure;
        TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

        //Setup timer for statemachine
        //Enable the TIM2 gloabal Interrupt
        NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 7;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);

        //TIM2 clock enable
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

        //Time base configuration
        TIM_TimeBaseStructure.TIM_Period = 500 - 1;  // 1 MHz down to 0.5 KHz (500 us)
        TIM_TimeBaseStructure.TIM_Prescaler = 84 - 1; // 24 MHz Clock down to 1 MHz (adjust per your clock)
        TIM_TimeBaseStructure.TIM_ClockDivision = 0;
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
        TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

        //TIM IT enable
        TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

        //TIM2 enable counter
        TIM_Cmd(TIM2, ENABLE);
}

void TIM2_IRQHandler(void)
{
        HandleSnesTimerIRQ();
}

enum SNES_CTRL_STATE
{
	START_LATCH = 0, END_LATCH,
	SHIFT1, SHIFT1_END,
	SHIFT2, SHIFT2_END,
	SHIFT3, SHIFT3_END,
	SHIFT4, SHIFT4_END,
	SHIFT5, SHIFT5_END,
	SHIFT6, SHIFT6_END,
	SHIFT7, SHIFT7_END,
	SHIFT8, SHIFT8_END,
	SHIFT9, SHIFT9_END,
	SHIFT10, SHIFT10_END,
	SHIFT11, SHIFT11_END,
	SHIFT12, SHIFT12_END,
	SHIFT13, SHIFT13_END,
	SHIFT14, SHIFT14_END,
	SHIFT15, SHIFT15_END,
	SHIFT16, SHIFT16_END
};

volatile enum SNES_CTRL_STATE state_ctrl = START_LATCH;

snes_button_state_t buttons_ctrl1 = {.raw = 0};
volatile uint16_t buttons_tmp_ctrl1 = 0;

snes_button_state_t buttons_ctrl2 = {.raw = 0};
volatile uint16_t buttons_tmp_ctrl2 = 0;

void InitializeSnesController(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	//Enable GPIO clocks
	RCC_AHB1PeriphClockCmd(GPIO_SNES1_LATCH_CLK | GPIO_SNES1_CLOCK_CLK | GPIO_SNES1_DATA_CLK, ENABLE);
	RCC_AHB1PeriphClockCmd(GPIO_SNES2_LATCH_CLK | GPIO_SNES2_CLOCK_CLK | GPIO_SNES2_DATA_CLK, ENABLE);

	//Configure data pins (Input, Pullup)
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_InitStructure.GPIO_Pin = GPIO_SNES1_DATA_PIN;
	GPIO_Init(GPIO_SNES1_DATA_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_SNES2_DATA_PIN;
	GPIO_Init(GPIO_SNES2_DATA_PORT, &GPIO_InitStructure);


	//Configure Latch and Clock pins
	//Latch (Output)
	//Clock (Output)
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_InitStructure.GPIO_Pin = GPIO_SNES1_LATCH_PIN;
	GPIO_Init(GPIO_SNES1_LATCH_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_SNES1_CLOCK_PIN;
	GPIO_Init(GPIO_SNES1_CLOCK_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_SNES2_LATCH_PIN;
	GPIO_Init(GPIO_SNES2_LATCH_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_SNES2_CLOCK_PIN;
	GPIO_Init(GPIO_SNES2_CLOCK_PORT, &GPIO_InitStructure);

	//Set clocks
	GPIO_SetBits(GPIO_SNES1_CLOCK_PORT, GPIO_SNES1_CLOCK_PIN);
	GPIO_SetBits(GPIO_SNES2_CLOCK_PORT, GPIO_SNES2_CLOCK_PIN);

	//Reset latchs
	GPIO_ResetBits(GPIO_SNES1_LATCH_PORT, GPIO_SNES1_LATCH_PIN);
	GPIO_ResetBits(GPIO_SNES2_LATCH_PORT, GPIO_SNES2_LATCH_PIN);
}

snes_button_state_t GetControllerState1(void)
{
	return buttons_ctrl1;
}

snes_button_state_t GetControllerState2(void)
{
	return buttons_ctrl2;
}

void HandleSnesTimerIRQ(void)
{
	//The if causes massive jitter in the VGA output, we currently don't need it anyways
	//if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

		switch(state_ctrl) {
			case START_LATCH:
				GPIO_SetBits(GPIO_SNES1_LATCH_PORT, GPIO_SNES1_LATCH_PIN);	//Latch = 1
				GPIO_SetBits(GPIO_SNES2_LATCH_PORT, GPIO_SNES2_LATCH_PIN);
				break;

			case END_LATCH:
				GPIO_ResetBits(GPIO_SNES1_LATCH_PORT, GPIO_SNES1_LATCH_PIN);	//Latch = 0
				GPIO_ResetBits(GPIO_SNES2_LATCH_PORT, GPIO_SNES2_LATCH_PIN);
				break;

			case SHIFT1:
			case SHIFT2:
			case SHIFT3:
			case SHIFT4:
			case SHIFT5:
			case SHIFT6:
			case SHIFT7:
			case SHIFT8:
			case SHIFT9:
			case SHIFT10:
			case SHIFT11:
			case SHIFT12:
			case SHIFT13:
			case SHIFT14:
			case SHIFT15:
			case SHIFT16:
				GPIO_ResetBits(GPIO_SNES1_CLOCK_PORT, GPIO_SNES1_CLOCK_PIN);	//Clock = 0
				GPIO_ResetBits(GPIO_SNES2_CLOCK_PORT, GPIO_SNES2_CLOCK_PIN);
				break;

			case SHIFT1_END:
			case SHIFT2_END:
			case SHIFT3_END:
			case SHIFT4_END:
			case SHIFT5_END:
			case SHIFT6_END:
			case SHIFT7_END:
			case SHIFT8_END:
			case SHIFT9_END:
			case SHIFT10_END:
			case SHIFT11_END:
			case SHIFT12_END:
			case SHIFT13_END:
			case SHIFT14_END:
			case SHIFT15_END:
			case SHIFT16_END:
				buttons_tmp_ctrl1 = (buttons_tmp_ctrl1 << 1) | GPIO_ReadInputDataBit(GPIO_SNES1_DATA_PORT, GPIO_SNES1_DATA_PIN);
				buttons_tmp_ctrl2 = (buttons_tmp_ctrl2 << 1) | GPIO_ReadInputDataBit(GPIO_SNES2_DATA_PORT, GPIO_SNES2_DATA_PIN);
				GPIO_SetBits(GPIO_SNES1_CLOCK_PORT, GPIO_SNES1_CLOCK_PIN);	//Clock = 1
				GPIO_SetBits(GPIO_SNES2_CLOCK_PORT, GPIO_SNES2_CLOCK_PIN);
				break;
		}

		if(state_ctrl == SHIFT16_END)
		{
			state_ctrl = START_LATCH;
			buttons_ctrl1.raw = ~buttons_tmp_ctrl1;
			buttons_ctrl2.raw = ~buttons_tmp_ctrl2;
		}
		else
			state_ctrl++;
	}
}
