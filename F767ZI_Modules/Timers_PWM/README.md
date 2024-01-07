# McMaster Formula Electric 
## *Timers and PWM readme documentation*
Authors: Samuel Parent and Dorian Knight
Last updated: 5/2/2021
Description: The Timer and PWM module allows you to set up timers and output PWM duty cycles

# References
- [Documentation](https://macformulaelectric899.sharepoint.com/:w:/s/Engineering/ERWY8rBVcMJKludiVqLavOYBiVmmONhMwQTp9xZT4cIRKQ?e=gznfSP)
- [Data Brief](https://www.st.com/resource/en/data_brief/nucleo-f767zi.pdf)
- [User Manual](https://www.st.com/resource/en/user_manual/dm00244518-stm32-nucleo144-boards-mb1137-stmicroelectronics.pdf)

## Build Status
Module Version: V1.0

## File Description
- **Timers_PWM_Testing** - Working test environment for the Timer and PWM library
- **ISR_On_Timer_Overflow_Function.txt** - A .txt file containing the ISR function code that must be pasted into your main.c code for the Interrupt service routine to work
- **timer_pwm_lib.h** - The timers and PWM library that will allow you to initialize timers and PWM outputs (more details on library below)

## Table of Contents 
- Feature overview
- Timer instructions
- PWM instructions
- ISR pastable code and instructions
- Terminology

### Features

- Set the period (milliseconds), ISR (boolean), ISR period (milliseconds) and channel (1-4) for up to two timers
- Using initialized timer, PWM can be initialized for a duty cycle on channels 1 through 4
--Allows for a total of 8 PWM outputs (4 per timer)
- PWM can be halted when given a specific timer and channel
- A timer can be halted on all channels when given a specific timer

### Timer Instructions
The parameters to initialize a timer include the following

- Timer number (1 or 2)
- Timer period (milliseconds)
- ISR enabled (boolean)
- Channel 1 (boolean)
- Channel 2 (boolean)
- Channel 3 (boolean)
- Channel 4 (boolean)
- ISR period (milliseconds)*

*ISR period must be a non zero multiple of the timer period

The Timer and PWM library has a special short cut for initializing a timer such that all you need to include is the timer **number** and **period**.

Three types of function calls can be used to initialize a timer
```
Timer_Init(timer#, period) 
```
- Timer enabled on all channels and ISR period is the same as the timer period
- Default arguments have handled most of the arguments, only timer number and period is absolutely necessary
```
Timer_Init(timer#, period, 1, 1, 1, 1, 1, ISR period) 
```
- The timer has been initialized on all channels, the ISR routine has been enabled and the period of that routine should either been equal to the timer period or be some scalar multiple of the timer period
- Using 1 as an argument enables while -1 disables 

```
- Timer_Init(timer#, period, .channel_1 = -1) 
```
- .param = value allows you to have specific control over a certain parameter. 
 
**IMPORTANT**: Using zero as a value is the same as not inputting anything. Use -1 for "false"

### PWM Instructions
The parameters to initialize a PWM output include the following

- Timer number (1 or 2)
- Channel number (1 through 4)
- Duty cycle (1 to 100 percent)

**NOTE**: PWM output will only work if the timer is valid and the channel is valid - meaning that the timer must already be initialized and the channel must be enabled. If not - the PWM output will not go through

### ISR Pastable code and Instructions

##### Preamble
The timer counts from 0 to 19,999 - after finishing the count it resets back to zero. If the ISR trigger was set to enabled during the initialization process, upon overflow the ISR routine code will be executed.

The ISR routine is housed within the HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) method.

If you want to run a segment of code upon timer overflow it must be within this HAL method. 

**The HAL method can be directly copied and pasted into your main.c code** and you should insert your code between the "User code here" and "User code ends" comments

The HAL function can also tell which timer has triggered the interrupt. This will allow you to set up different interrupt service routines depending on which timer has overflowed.

*Note*: If your ISR period was set to a non zero multiple of the timer period then the interrupt service routine will run every time the ISR period is complete. Ex: ISR period is 2x the timer period. The ISR will run every second time the timer overflows

##### Code
Please follow the link and copy and paste the ISR template into your main.c code

[ISR Routine](https://gitlab.com/MACFormulaElectric/stm32-mcu/-/blob/timers_and_pwm_V1.0/VCU_Modules/ISR_On_Timer_Overflow_Function.txt)

### Terminology
- Duty cycle - The percent of time for which a signal is on (ex duty cycle of 50% means that the signal will be on 50% of the time and then off the other 50%)
- ISR - Interrupt Service Routine
- Period - The time it takes for the timer to complete one full cycle (count from 0 to 19,999)
- PWM - Pulse Width Modulation


