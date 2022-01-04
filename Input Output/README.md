# Input Output RL78/G14-R5F104PJA (RSKRL78G14 Development board)

Whenever the embedded  system engineer has experience with a special microcontroller, when he starts using a new microcontroller,
he needs to start with the input and output pins, the first example that starts to be used is the LED tilting.

This example gives you a simple overview of the use of input, output, and external interrupt.
In this example I used 3 outputs and 3 inputs with 2 as the external interrupt, and a timer for 500us used to activate the flgs which I used it to manage my example like generating a dely.

# Tools used  
1. Applilet3 for RL78 version 3.02 used to configure the project is a code generator.
2. IAR Embedded Worckbench for Renesas RL78 version4.21.1
3. RSKRL78G14 Development board with RL78/G14-R5F104PJA microcontroller 
4. Renesas E1 programmer 

# How this exampel works 
- one of the LEDs, LED3 stay blinking each 500ms.
- when switch 3 is pressed, LED2 turns ON otherwise it goes OFF.
- when switch 1 is pressed, the LED0 and LED1 will blinking and turned OFF.

Renesas(RSKRL78G14) Starter Kit User’s Manual page 17.
 ![dev_board_led_switch_pins][E:\ibrahim\Github_ibrahim\Renesas RL78_G14\Renesas-RL78\Input Output\images\dev_board_leds_and_switches_pins.png] 
























Executable files built outside of IAR Embedded Workbench

Follow these steps to load and debug an executable file that was built outside
IAR Embedded Workbench, for example projects built on the command line. 

1. Choose Project>Add Files to add the executable file (filename extension out)
that you want to debug to the project. 

2. Set up the debugger options according to you needs. The only project options
that are meaningful to set for this kind of project are options in the General
Options and Debugger categories. Make sure to set up the general project 
options in the same way as when the executable file was built.

3. To start the debugger, select the project in the workspace window and
click the Debug button. The project can be reused whenever you rebuild your
executable file. The debugger will notice if the executable file has been 
rebuilt and ask you if you want to reload it.
