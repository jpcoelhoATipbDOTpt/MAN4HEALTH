[
    {
        "id": "d83c6230051c6299",
        "type": "tab",
        "label": "Pluviometro dashboard",
        "disabled": false,
        "info": "",
        "env": []
    },
    {
        "id": "cc63246fc83f064b",
        "type": "mqtt in",
        "z": "d83c6230051c6299",
        "name": "",
        "topic": "/man4health/json/meteo/pluviodev1/attrs",
        "qos": "2",
        "datatype": "auto",
        "broker": "a7f68a32698ddb0f",
        "nl": false,
        "rap": true,
        "rh": 0,
        "inputs": 0,
        "x": 200,
        "y": 60,
        "wires": [
            [
                "b2f83480b9b7d57a",
                "722b0ace8dae4311",
                "2bcd4d0aec2b3281",
                "1ee77e1f4aa3f9ad",
                "f15f5bc1a8e6ecde"
            ]
        ]
    },
    {
        "id": "b2f83480b9b7d57a",
        "type": "debug",
        "z": "d83c6230051c6299",
        "name": "debug 2",
        "active": true,
        "tosidebar": true,
        "console": false,
        "tostatus": false,
        "complete": "false",
        "statusVal": "",
        "statusType": "auto",
        "x": 600,
        "y": 60,
        "wires": []
    },
    {
        "id": "b4315196d34dcb48",
        "type": "function",
        "z": "d83c6230051c6299",
        "name": "",
        "func": "msg.payload = msg.payload = Math.round(msg.payload.TA*10)/10\nreturn msg;",
        "outputs": 1,
        "timeout": "",
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 440,
        "y": 360,
        "wires": [
            [
                "e9d1804a6aae2239",
                "04bf08efd41801be"
            ]
        ]
    },
    {
        "id": "722b0ace8dae4311",
        "type": "json",
        "z": "d83c6230051c6299",
        "name": "",
        "property": "payload",
        "action": "",
        "pretty": false,
        "x": 270,
        "y": 200,
        "wires": [
            [
                "c8832a6375d117a4"
            ]
        ]
    },
    {
        "id": "c8832a6375d117a4",
        "type": "function",
        "z": "d83c6230051c6299",
        "name": "",
        "func": "msg.payload = msg.payload = Math.round(msg.payload.AC*10)/10\nreturn msg;",
        "outputs": 1,
        "timeout": "",
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 440,
        "y": 200,
        "wires": [
            [
                "71f86b9c29a0757a",
                "7bd87b059a781a4b"
            ]
        ]
    },
    {
        "id": "71f86b9c29a0757a",
        "type": "ui_chart",
        "z": "d83c6230051c6299",
        "name": "",
        "group": "fcb68fc2ff6989ae",
        "order": 1,
        "width": 0,
        "height": 0,
        "label": "Accumulated (since last check)/mm",
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
        "x": 700,
        "y": 200,
        "wires": [
            []
        ]
    },
    {
        "id": "7bd87b059a781a4b",
        "type": "ui_gauge",
        "z": "d83c6230051c6299",
        "name": "",
        "group": "d3e0eaeffca12f6c",
        "order": 1,
        "width": 0,
        "height": 0,
        "gtype": "gage",
        "title": "Accumulated/mm",
        "label": "units",
        "format": "{{value}}",
        "min": "0",
        "max": "10",
        "colors": [
            "#00b500",
            "#e6e600",
            "#ca3838"
        ],
        "seg1": "",
        "seg2": "",
        "diff": false,
        "className": "",
        "x": 650,
        "y": 240,
        "wires": []
    },
    {
        "id": "8cf7a05a4c025ad6",
        "type": "ui_chart",
        "z": "d83c6230051c6299",
        "name": "",
        "group": "fcb68fc2ff6989ae",
        "order": 3,
        "width": 0,
        "height": 0,
        "label": "Event Accumulated/mm",
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
        "x": 670,
        "y": 280,
        "wires": [
            []
        ]
    },
    {
        "id": "851f7c902258b6fa",
        "type": "ui_gauge",
        "z": "d83c6230051c6299",
        "name": "",
        "group": "d3e0eaeffca12f6c",
        "order": 2,
        "width": 0,
        "height": 0,
        "gtype": "gage",
        "title": "Event Accumulated/mm",
        "label": "units",
        "format": "{{value}}",
        "min": 0,
        "max": "10",
        "colors": [
            "#00b500",
            "#e6e600",
            "#ca3838"
        ],
        "seg1": "",
        "seg2": "",
        "diff": false,
        "className": "",
        "x": 670,
        "y": 320,
        "wires": []
    },
    {
        "id": "e9d1804a6aae2239",
        "type": "ui_chart",
        "z": "d83c6230051c6299",
        "name": "",
        "group": "fcb68fc2ff6989ae",
        "order": 4,
        "width": 0,
        "height": 0,
        "label": "Total Accumulated/mm",
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
        "x": 660,
        "y": 360,
        "wires": [
            []
        ]
    },
    {
        "id": "04bf08efd41801be",
        "type": "ui_gauge",
        "z": "d83c6230051c6299",
        "name": "",
        "group": "d3e0eaeffca12f6c",
        "order": 3,
        "width": 0,
        "height": 0,
        "gtype": "gage",
        "title": "Total Accumulated/mm",
        "label": "units",
        "format": "{{value}}",
        "min": 0,
        "max": "10000",
        "colors": [
            "#00b500",
            "#e6e600",
            "#ca3838"
        ],
        "seg1": "",
        "seg2": "",
        "diff": false,
        "className": "",
        "x": 660,
        "y": 400,
        "wires": []
    },
    {
        "id": "d536b09da90595f7",
        "type": "function",
        "z": "d83c6230051c6299",
        "name": "",
        "func": "msg.payload = msg.payload = Math.round(msg.payload.EA*10)/10\nreturn msg;",
        "outputs": 1,
        "timeout": "",
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 440,
        "y": 280,
        "wires": [
            [
                "8cf7a05a4c025ad6",
                "851f7c902258b6fa"
            ]
        ]
    },
    {
        "id": "2bcd4d0aec2b3281",
        "type": "json",
        "z": "d83c6230051c6299",
        "name": "",
        "property": "payload",
        "action": "",
        "pretty": false,
        "x": 270,
        "y": 280,
        "wires": [
            [
                "d536b09da90595f7"
            ]
        ]
    },
    {
        "id": "1ee77e1f4aa3f9ad",
        "type": "json",
        "z": "d83c6230051c6299",
        "name": "",
        "property": "payload",
        "action": "",
        "pretty": false,
        "x": 270,
        "y": 360,
        "wires": [
            [
                "b4315196d34dcb48"
            ]
        ]
    },
    {
        "id": "f15f5bc1a8e6ecde",
        "type": "json",
        "z": "d83c6230051c6299",
        "name": "",
        "property": "payload",
        "action": "",
        "pretty": false,
        "x": 270,
        "y": 440,
        "wires": [
            [
                "3a15d4bc22e3b41f"
            ]
        ]
    },
    {
        "id": "3a15d4bc22e3b41f",
        "type": "function",
        "z": "d83c6230051c6299",
        "name": "",
        "func": "msg.payload = msg.payload = Math.round(msg.payload.RI*10)/10\nreturn msg;",
        "outputs": 1,
        "timeout": "",
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 440,
        "y": 440,
        "wires": [
            [
                "b80ac472966e8f32",
                "5112f821f73f1ac3"
            ]
        ]
    },
    {
        "id": "b80ac472966e8f32",
        "type": "ui_chart",
        "z": "d83c6230051c6299",
        "name": "",
        "group": "fcb68fc2ff6989ae",
        "order": 4,
        "width": 0,
        "height": 0,
        "label": "R int/mm/h",
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
        "x": 630,
        "y": 440,
        "wires": [
            []
        ]
    },
    {
        "id": "5112f821f73f1ac3",
        "type": "ui_gauge",
        "z": "d83c6230051c6299",
        "name": "",
        "group": "d3e0eaeffca12f6c",
        "order": 4,
        "width": 0,
        "height": 0,
        "gtype": "gage",
        "title": "Rint/mm/h",
        "label": "units",
        "format": "{{value}}",
        "min": 0,
        "max": "10",
        "colors": [
            "#00b500",
            "#e6e600",
            "#ca3838"
        ],
        "seg1": "",
        "seg2": "",
        "diff": false,
        "className": "",
        "x": 630,
        "y": 480,
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
        "id": "fcb68fc2ff6989ae",
        "type": "ui_group",
        "name": "PLUVIO MODULE (chart)",
        "tab": "dc465c75df0ff14a",
        "order": 3,
        "disp": true,
        "width": "6",
        "collapse": false,
        "className": ""
    },
    {
        "id": "d3e0eaeffca12f6c",
        "type": "ui_group",
        "name": "PLUVIO MODULE (gauge)",
        "tab": "dc465c75df0ff14a",
        "order": 4,
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
