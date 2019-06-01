# OverheatInspection

This is a project to control overheating equipment. System notifies interested parties in case of an overheat.

There is a big market for overheat detection overall, submarkets could be examplified as server industry, UPS industry and refrigerator industry.

![One Pager Poster](https://github.com/bounIoT/OverheatInspection/blob/master/Documents/Overheat%20Inspection%20One%20Pager.jpg)

### Team Members

* Ahmet Melek - www.ahmetmelek.com 
* Cumhur Kılıç - https://www.linkedin.com/in/cumhur-k%C4%B1l%C4%B1%C3%A7-530a23140/


### Introduction of the Project

Components: 

![Components](https://github.com/bounIoT/OverheatInspection/blob/master/Documents/Components%20List%20Overheat%20Control.jpg)

Communication Flow:

![Communication Flow](https://github.com/bounIoT/OverheatInspection/blob/master/Documents/Communication%20Flow%20Overheat%20Control.jpg)

Circuit Schema:

![Circuit Schema](https://github.com/bounIoT/OverheatInspection/blob/master/Documents/Circuit%20Schema%20Overheat%20Control.jpg)


## Setup

### Steps

* Create an IBM cloud account, create an app, create a Watson IoT service.
* Connect your Arduino Yun device to your machine. 
* Configure your Arduino Yun to connect to a Wifi nearby.
* Modify the .ino code. Modify "IBM Watson IoT Platform Details" section with your own credentials of Watson IoT.
* Upload .ino code, residing in "Node" folder; to your Arduino Yun.
* Go to your Node Red web editor with "Go to App Url" option in Watson IoT. Open a flow.
* Click the menu button (button with three bars). Click import, import from clipboard.
* Paste the one-lined json file residing in "Cloud" folder to the text box. Upload the file.

### If all is right

* You should see logs in your local Arduino IDE -> Tools -> Serial Monitor
* There should be opened connections in your Watson Iotf Service dashboard. (inside logs section)
* You should be able to see gauge and plot UI in Node Red dashboard.

### To open Node Red Dashboard

* Click on the little statistics button in the top right of your flow editor.
* You should be seeing buttons "Layout", "Site", "Theme". On the right of "Theme" button, click on the little arrow button.


## Description of system's operation pipeline

Here we explain the steps that the system takes to provide overheat control service.

* Arduino Yun measures the voltage going by the thermistor branches of the circuit, with analog pins.
* Embedded code translates these voltage values (which are translated to 10 bit data inside arduino) to temperature values.
* Arduino Yun connects to a nearby Wifi, uploads the data to IBM Cloud.
* Node Red code deployed inside IBM Cloud checks if there is any abnormal values, overheating, or faulty behaviour of the sensors.
* If there is an abnormaly, twilio nodes are activated and a message to the related personnel is sent.
* Node red also carries the information to the dashboard page.
