[
    {
        "id": "3bd5f5836472422a",
        "type": "tab",
        "label": "CO2 dashboard",
        "disabled": false,
        "info": "",
        "env": []
    },
    {
        "id": "c5461a9e7b01c668",
        "type": "mqtt in",
        "z": "3bd5f5836472422a",
        "name": "",
        "topic": "/man4health/json/meteo/co2dev1/attrs",
        "qos": "2",
        "datatype": "auto",
        "broker": "a7f68a32698ddb0f",
        "nl": false,
        "rap": true,
        "rh": 0,
        "inputs": 0,
        "x": 210,
        "y": 140,
        "wires": [
            [
                "613cc463eab8cbb6",
                "8a3a7f814f0eaa4b",
                "6e1f382030a4d6da",
                "5f8da42ec7a26f12"
            ]
        ]
    },
    {
        "id": "613cc463eab8cbb6",
        "type": "debug",
        "z": "3bd5f5836472422a",
        "name": "debug 1",
        "active": true,
        "tosidebar": true,
        "console": false,
        "tostatus": false,
        "complete": "false",
        "statusVal": "",
        "statusType": "auto",
        "x": 620,
        "y": 140,
        "wires": []
    },
    {
        "id": "c3659d346fef727f",
        "type": "ui_chart",
        "z": "3bd5f5836472422a",
        "name": "",
        "group": "d3fa78d7515cd917",
        "order": 1,
        "width": 0,
        "height": 0,
        "label": "Air Temperature/ºC",
        "chartType": "line",
        "legend": "false",
        "xformat": "HH:mm:ss",
        "interpolate": "linear",
        "nodata": "",
        "dot": false,
        "ymin": "-10",
        "ymax": "50",
        "removeOlder": 1,
        "removeOlderPoints": "",
        "removeOlderUnit": "86400",
        "cutout": 0,
        "useOneColor": false,
        "useUTC": false,
        "colors": [
            "#1f77b4",
            "#aec7e8",
            "#ff7f0e",
            "#2ca02c",
            "#98df8a",
            "#d62728",
            "#ff9896",
            "#9467bd",
            "#c5b0d5"
        ],
        "outputs": 1,
        "useDifferentColor": false,
        "className": "",
        "x": 690,
        "y": 200,
        "wires": [
            []
        ]
    },
    {
        "id": "8a3a7f814f0eaa4b",
        "type": "json",
        "z": "3bd5f5836472422a",
        "name": "",
        "property": "payload",
        "action": "",
        "pretty": false,
        "x": 310,
        "y": 200,
        "wires": [
            [
                "933767d4f28cc1be"
            ]
        ]
    },
    {
        "id": "933767d4f28cc1be",
        "type": "function",
        "z": "3bd5f5836472422a",
        "name": "",
        "func": "msg.payload = msg.payload = Math.round(msg.payload.AT*10)/10\nreturn msg;",
        "outputs": 1,
        "timeout": "",
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 480,
        "y": 200,
        "wires": [
            [
                "c3659d346fef727f",
                "2f8919ba3c8a5770"
            ]
        ]
    },
    {
        "id": "6e1f382030a4d6da",
        "type": "json",
        "z": "3bd5f5836472422a",
        "name": "",
        "property": "payload",
        "action": "",
        "pretty": false,
        "x": 310,
        "y": 280,
        "wires": [
            [
                "a78020aa441ada90"
            ]
        ]
    },
    {
        "id": "a78020aa441ada90",
        "type": "function",
        "z": "3bd5f5836472422a",
        "name": "",
        "func": "msg.payload = msg.payload = Math.round(msg.payload.AM*10)/10\nreturn msg;",
        "outputs": 1,
        "timeout": "",
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 480,
        "y": 280,
        "wires": [
            [
                "2c7dc663972b107c",
                "3d2700ad24617e80"
            ]
        ]
    },
    {
        "id": "2c7dc663972b107c",
        "type": "ui_chart",
        "z": "3bd5f5836472422a",
        "name": "",
        "group": "d3fa78d7515cd917",
        "order": 3,
        "width": 0,
        "height": 0,
        "label": "Air Moisture/%",
        "chartType": "line",
        "legend": "false",
        "xformat": "HH:mm:ss",
        "interpolate": "linear",
        "nodata": "",
        "dot": false,
        "ymin": "0",
        "ymax": "100",
        "removeOlder": 1,
        "removeOlderPoints": "",
        "removeOlderUnit": "86400",
        "cutout": 0,
        "useOneColor": false,
        "useUTC": false,
        "colors": [
            "#1f77b4",
            "#aec7e8",
            "#ff7f0e",
            "#2ca02c",
            "#98df8a",
            "#d62728",
            "#ff9896",
            "#9467bd",
            "#c5b0d5"
        ],
        "outputs": 1,
        "useDifferentColor": false,
        "className": "",
        "x": 680,
        "y": 280,
        "wires": [
            []
        ]
    },
    {
        "id": "5f8da42ec7a26f12",
        "type": "json",
        "z": "3bd5f5836472422a",
        "name": "",
        "property": "payload",
        "action": "",
        "pretty": false,
        "x": 310,
        "y": 360,
        "wires": [
            [
                "a0f384671e8b0ad3"
            ]
        ]
    },
    {
        "id": "a0f384671e8b0ad3",
        "type": "function",
        "z": "3bd5f5836472422a",
        "name": "",
        "func": "msg.payload = msg.payload = Math.round(msg.payload.CO2*10)/10\nreturn msg;",
        "outputs": 1,
        "timeout": "",
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 480,
        "y": 360,
        "wires": [
            [
                "47e1848dcf9f83b8",
                "efc1fd2301fb9fcc"
            ]
        ]
    },
    {
        "id": "47e1848dcf9f83b8",
        "type": "ui_chart",
        "z": "3bd5f5836472422a",
        "name": "",
        "group": "d3fa78d7515cd917",
        "order": 4,
        "width": 0,
        "height": 0,
        "label": "CO2 concentration/ppm",
        "chartType": "line",
        "legend": "false",
        "xformat": "HH:mm:ss",
        "interpolate": "linear",
        "nodata": "",
        "dot": false,
        "ymin": "0",
        "ymax": "1000",
        "removeOlder": 1,
        "removeOlderPoints": "",
        "removeOlderUnit": "86400",
        "cutout": 0,
        "useOneColor": false,
        "useUTC": false,
        "colors": [
            "#1f77b4",
            "#aec7e8",
            "#ff7f0e",
            "#2ca02c",
            "#98df8a",
            "#d62728",
            "#ff9896",
            "#9467bd",
            "#c5b0d5"
        ],
        "outputs": 1,
        "useDifferentColor": false,
        "className": "",
        "x": 710,
        "y": 360,
        "wires": [
            []
        ]
    },
    {
        "id": "2f8919ba3c8a5770",
        "type": "ui_gauge",
        "z": "3bd5f5836472422a",
        "name": "",
        "group": "fc25d46192fb17e4",
        "order": 4,
        "width": 0,
        "height": 0,
        "gtype": "gage",
        "title": "Air Temperature/ºC",
        "label": "units",
        "format": "{{value}}",
        "min": "-10",
        "max": "50",
        "colors": [
            "#00b500",
            "#e6e600",
            "#ca3838"
        ],
        "seg1": "",
        "seg2": "",
        "diff": false,
        "className": "",
        "x": 690,
        "y": 240,
        "wires": []
    },
    {
        "id": "3d2700ad24617e80",
        "type": "ui_gauge",
        "z": "3bd5f5836472422a",
        "name": "",
        "group": "fc25d46192fb17e4",
        "order": 5,
        "width": 0,
        "height": 0,
        "gtype": "gage",
        "title": "Air Moisture/%",
        "label": "units",
        "format": "{{value}}",
        "min": 0,
        "max": "100",
        "colors": [
            "#00b500",
            "#e6e600",
            "#ca3838"
        ],
        "seg1": "",
        "seg2": "",
        "diff": false,
        "className": "",
        "x": 680,
        "y": 320,
        "wires": []
    },
    {
        "id": "efc1fd2301fb9fcc",
        "type": "ui_gauge",
        "z": "3bd5f5836472422a",
        "name": "",
        "group": "fc25d46192fb17e4",
        "order": 6,
        "width": 0,
        "height": 0,
        "gtype": "gage",
        "title": "CO2 Concentration/ppm",
        "label": "units",
        "format": "{{value}}",
        "min": 0,
        "max": "1000",
        "colors": [
            "#00b500",
            "#e6e600",
            "#ca3838"
        ],
        "seg1": "",
        "seg2": "",
        "diff": false,
        "className": "",
        "x": 710,
        "y": 400,
        "wires": []
    },
    {
        "id": "a7f68a32698ddb0f",
        "type": "mqtt-broker",
        "name": "man4health",
        "broker": "193.136.195.25",
        "port": "1883",
        "clientid": "NODE_RED_Client",
        "usetls": false,
        "protocolVersion": "4",
        "keepalive": "60",
        "cleansession": true,
        "birthTopic": "",
        "birthQos": "0",
        "birthPayload": "",
        "birthMsg": {},
        "closeTopic": "",
        "closeQos": "0",
        "closePayload": "",
        "closeMsg": {},
        "willTopic": "",
        "willQos": "0",
        "willPayload": "",
        "willMsg": {},
        "sessionExpiry": ""
    },
    {
        "id": "d3fa78d7515cd917",
        "type": "ui_group",
        "name": "CO2 MODULE (charts)",
        "tab": "dc465c75df0ff14a",
        "order": 1,
        "disp": true,
        "width": "6",
        "collapse": false,
        "className": ""
    },
    {
        "id": "fc25d46192fb17e4",
        "type": "ui_group",
        "name": "CO2 MODULE (gauges)",
        "tab": "dc465c75df0ff14a",
        "order": 2,
        "disp": true,
        "width": "6",
        "collapse": false,
        "className": ""
    },
    {
        "id": "dc465c75df0ff14a",
        "type": "ui_tab",
        "name": "LOCAL DATA",
        "icon": "dashboard",
        "disabled": false,
        "hidden": false
    }
]
