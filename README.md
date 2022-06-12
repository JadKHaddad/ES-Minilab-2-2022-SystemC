# ES Minilab 2 - SystemC - 2022
## Maps annotations
* **[0]** unknown
* **[1]** discovered
* **[2]** to be discovered
* **[3]** dicovered, a drone is in location
* **[99]** statically blocked
* **[-1]** free, can be discovered 
## Usage
Define map size and drones count in ```const.hpp```<br>
Define scenarios in ```controller.hpp```<br> 
Use your own Makefile.
## Output
See ```output``` for scenarios outputs.<br>
* **scenario_1_3_drones:** success
* **scenario_1_5_drones:** success
* **scenario_1_10_drones:** success
<br><br>
* **scenario_2_3_drones:** battery dies
* **scenario_2_5_drones:** battery dies
* **scenario_2_10_drones:** success
<br><br>
* **scenario_3_3_drones:** battery dies
* **scenario_3_5_drones:** battery dies
* **scenario_3_10_drones:** battery dies
* **scenario_3_20_drones:** battery dies
* **scenario_3_40_drones:** battery dies
* **scenario_3_60_drones:** battery dies
* **scenario_3_120_drones:** success