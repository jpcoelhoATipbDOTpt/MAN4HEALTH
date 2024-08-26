[
    {
        "id": "c50bbe8c23efb028",
        "type": "tab",
        "label": "EPEVER dahsboard",
        "disabled": false,
        "info": ""
    },
    {
        "id": "92bf329c9e04c0cf",
        "type": "mqtt in",
        "z": "c50bbe8c23efb028",
        "name": "",
        "topic": "/man4health/json/fiware/tracer_a1210al01/attrs",
        "qos": "2",
        "datatype": "auto",
        "broker": "a7f68a32698ddb0f",
        "nl": false,
        "rap": true,
        "rh": 0,
        "inputs": 0,
        "x": 220,
        "y": 100,
        "wires": [
            [
                "51921e14b96188ca"
            ]
        ]
    },
    {
        "id": "daeae736289c8408",
        "type": "debug",
        "z": "c50bbe8c23efb028",
        "name": "",
        "active": true,
        "tosidebar": true,
        "console": false,
        "tostatus": false,
        "complete": "false",
        "statusVal": "",
        "statusType": "auto",
        "x": 1170,
        "y": 640,
        "wires": []
    },
    {
        "id": "b5f64923a6edc441",
        "type": "inject",
        "z": "c50bbe8c23efb028",
        "name": "",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "fakenode",
        "payload": "ola",
        "payloadType": "str",
        "x": 130,
        "y": 460,
        "wires": [
            [
                "0c58754293cb1d9c"
            ]
        ]
    },
    {
        "id": "0c58754293cb1d9c",
        "type": "mqtt out",
        "z": "c50bbe8c23efb028",
        "name": "",
        "topic": "/man4health/json/iot",
        "qos": "",
        "retain": "",
        "respTopic": "",
        "contentType": "",
        "userProps": "",
        "correl": "",
        "expiry": "",
        "broker": "a7f68a32698ddb0f",
        "x": 380,
        "y": 460,
        "wires": []
    },
    {
        "id": "e47b4649c852c754",
        "type": "comment",
        "z": "c50bbe8c23efb028",
        "name": "Data from EPEVER",
        "info": "Data from EPEVER",
        "x": 130,
        "y": 60,
        "wires": []
    },
    {
        "id": "51921e14b96188ca",
        "type": "json",
        "z": "c50bbe8c23efb028",
        "name": "",
        "property": "payload",
        "action": "",
        "pretty": false,
        "x": 490,
        "y": 100,
        "wires": [
            [
                "9279e89482ea418d",
                "da7c972c70783830",
                "a14bb624d83775fb",
                "d4c999f667c81e0e",
                "ae75c0364b4e5948",
                "7b719eb9d755698d",
                "f1b1c3cfecf52887",
                "023d563086b23d56",
                "50a6471a59dfce29",
                "dfc1471edaaa3d95",
                "5b3de3032f78e203",
                "c14989dbec16f6ea",
                "64f7db4f54fe97cb",
                "aa02e72b2ac84ffd",
                "0b85effe64a1b2d6",
                "06da6e47ce174595",
                "3a7f8303708ac5a2",
                "298af65a43e9620f",
                "0965fdc21909615c"
            ]
        ]
    },
    {
        "id": "9279e89482ea418d",
        "type": "function",
        "z": "c50bbe8c23efb028",
        "name": "",
        "func": "msg.payload = msg.payload = Math.round(msg.payload.A3*10)/10\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 640,
        "y": 100,
        "wires": [
            [
                "2d22e63202c03195"
            ]
        ]
    },
    {
        "id": "2d22e63202c03195",
        "type": "ui_chart",
        "z": "c50bbe8c23efb028",
        "name": "",
        "group": "7abb7779e3d4bc3c",
        "order": 1,
        "width": "6",
        "height": "4",
        "label": "PV array Input Voltage",
        "chartType": "line",
        "legend": "false",
        "xformat": "HH:mm:ss",
        "interpolate": "linear",
        "nodata": "",
        "dot": false,
        "ymin": "0",
        "ymax": "50",
        "removeOlder": 1,
        "removeOlderPoints": "144",
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
        "x": 840,
        "y": 100,
        "wires": [
            []
        ]
    },
    {
        "id": "cd3f9cda8dd1b1e8",
        "type": "ui_gauge",
        "z": "c50bbe8c23efb028",
        "name": "",
        "group": "72208f30aed9593a",
        "order": 0,
        "width": 0,
        "height": 0,
        "gtype": "gage",
        "title": "Minimum Battery Voltage/Today",
        "label": "Volts",
        "format": "{{value}}",
        "min": 0,
        "max": "20",
        "colors": [
            "#ff7070",
            "#f00000",
            "#811313"
        ],
        "seg1": "",
        "seg2": "",
        "diff": false,
        "className": "",
        "x": 870,
        "y": 460,
        "wires": []
    },
    {
        "id": "a29f4707497d347e",
        "type": "ui_gauge",
        "z": "c50bbe8c23efb028",
        "name": "",
        "group": "b4e0c3891df63f73",
        "order": 3,
        "width": 0,
        "height": 0,
        "gtype": "gage",
        "title": "Battery SOC",
        "label": "units",
        "format": "{{value}}",
        "min": 0,
        "max": "1",
        "colors": [
            "#00b500",
            "#e6e600",
            "#ca3838"
        ],
        "seg1": "",
        "seg2": "",
        "diff": false,
        "className": "",
        "x": 810,
        "y": 380,
        "wires": []
    },
    {
        "id": "e12a2ee3a22e3cd1",
        "type": "ui_chart",
        "z": "c50bbe8c23efb028",
        "name": "",
        "group": "649e58d23e4dde41",
        "order": 3,
        "width": "6",
        "height": "4",
        "label": "Load Voltage",
        "chartType": "line",
        "legend": "false",
        "xformat": "HH:mm:ss",
        "interpolate": "linear",
        "nodata": "No Data",
        "dot": false,
        "ymin": "0",
        "ymax": "20",
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
        "x": 810,
        "y": 180,
        "wires": [
            []
        ]
    },
    {
        "id": "da7c972c70783830",
        "type": "function",
        "z": "c50bbe8c23efb028",
        "name": "",
        "func": "msg.payload = msg.payload = Math.round(msg.payload.A4*10)/10\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 640,
        "y": 140,
        "wires": [
            [
                "4da2bd2c669f14a1"
            ]
        ]
    },
    {
        "id": "4da2bd2c669f14a1",
        "type": "ui_chart",
        "z": "c50bbe8c23efb028",
        "name": "",
        "group": "7abb7779e3d4bc3c",
        "order": 2,
        "width": "6",
        "height": "4",
        "label": "PV array Input Current",
        "chartType": "line",
        "legend": "false",
        "xformat": "HH:mm:ss",
        "interpolate": "linear",
        "nodata": "No data",
        "dot": false,
        "ymin": "0",
        "ymax": "10",
        "removeOlder": 1,
        "removeOlderPoints": "144",
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
        "x": 840,
        "y": 140,
        "wires": [
            []
        ]
    },
    {
        "id": "a14bb624d83775fb",
        "type": "function",
        "z": "c50bbe8c23efb028",
        "name": "",
        "func": "msg.payload = msg.payload = Math.round(msg.payload.A7*10)/10\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 640,
        "y": 180,
        "wires": [
            [
                "e12a2ee3a22e3cd1"
            ]
        ]
    },
    {
        "id": "d4c999f667c81e0e",
        "type": "function",
        "z": "c50bbe8c23efb028",
        "name": "",
        "func": "msg.payload = msg.payload = Math.round(msg.payload.A8*10)/10\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 640,
        "y": 220,
        "wires": [
            [
                "786e5e6d644148a7"
            ]
        ]
    },
    {
        "id": "786e5e6d644148a7",
        "type": "ui_chart",
        "z": "c50bbe8c23efb028",
        "name": "",
        "group": "649e58d23e4dde41",
        "order": 3,
        "width": "6",
        "height": "4",
        "label": "Load Current",
        "chartType": "line",
        "legend": "false",
        "xformat": "HH:mm:ss",
        "interpolate": "linear",
        "nodata": "No Data",
        "dot": false,
        "ymin": "0",
        "ymax": "20",
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
        "x": 810,
        "y": 220,
        "wires": [
            []
        ]
    },
    {
        "id": "ae75c0364b4e5948",
        "type": "function",
        "z": "c50bbe8c23efb028",
        "name": "",
        "func": "msg.payload = msg.payload = Math.round(msg.payload.A9*10)/10\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 640,
        "y": 260,
        "wires": [
            [
                "d3718e031bdc3b30"
            ]
        ]
    },
    {
        "id": "d3718e031bdc3b30",
        "type": "ui_chart",
        "z": "c50bbe8c23efb028",
        "name": "",
        "group": "649e58d23e4dde41",
        "order": 3,
        "width": "6",
        "height": "4",
        "label": "Load Power",
        "chartType": "line",
        "legend": "false",
        "xformat": "HH:mm:ss",
        "interpolate": "linear",
        "nodata": "No Data",
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
        "x": 810,
        "y": 260,
        "wires": [
            []
        ]
    },
    {
        "id": "7b719eb9d755698d",
        "type": "function",
        "z": "c50bbe8c23efb028",
        "name": "",
        "func": "msg.payload = msg.payload = Math.round(msg.payload.A11*10)/10\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 640,
        "y": 300,
        "wires": [
            [
                "8cc523e46027fe59"
            ]
        ]
    },
    {
        "id": "8cc523e46027fe59",
        "type": "ui_chart",
        "z": "c50bbe8c23efb028",
        "name": "",
        "group": "72208f30aed9593a",
        "order": 3,
        "width": "6",
        "height": "4",
        "label": "Battery Temperature",
        "chartType": "line",
        "legend": "false",
        "xformat": "HH:mm:ss",
        "interpolate": "linear",
        "nodata": "No Data",
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
        "x": 840,
        "y": 300,
        "wires": [
            []
        ]
    },
    {
        "id": "f1b1c3cfecf52887",
        "type": "function",
        "z": "c50bbe8c23efb028",
        "name": "",
        "func": "msg.payload = msg.payload = Math.round(msg.payload.A13*10)/10\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 640,
        "y": 380,
        "wires": [
            [
                "a29f4707497d347e"
            ]
        ]
    },
    {
        "id": "de63e9e53eb3bc60",
        "type": "comment",
        "z": "c50bbe8c23efb028",
        "name": "",
        "info": "The percentage of battery's remaining capacity",
        "x": 940,
        "y": 380,
        "wires": []
    },
    {
        "id": "023d563086b23d56",
        "type": "function",
        "z": "c50bbe8c23efb028",
        "name": "",
        "func": "msg.payload = msg.payload = Math.round(msg.payload.A18*10)/10\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 640,
        "y": 420,
        "wires": [
            [
                "bb5a86d7bed6c4c5"
            ]
        ]
    },
    {
        "id": "50a6471a59dfce29",
        "type": "function",
        "z": "c50bbe8c23efb028",
        "name": "",
        "func": "msg.payload = msg.payload = Math.round(msg.payload.A19*10)/10\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 640,
        "y": 460,
        "wires": [
            [
                "cd3f9cda8dd1b1e8"
            ]
        ]
    },
    {
        "id": "bb5a86d7bed6c4c5",
        "type": "ui_gauge",
        "z": "c50bbe8c23efb028",
        "name": "",
        "group": "72208f30aed9593a",
        "order": 0,
        "width": 0,
        "height": 0,
        "gtype": "gage",
        "title": "Maximum Battery Voltage/Today",
        "label": "Volts",
        "format": "{{value}}",
        "min": 0,
        "max": "20",
        "colors": [
            "#00b500",
            "#257e2b",
            "#27381f"
        ],
        "seg1": "",
        "seg2": "",
        "diff": false,
        "className": "",
        "x": 870,
        "y": 420,
        "wires": []
    },
    {
        "id": "dfc1471edaaa3d95",
        "type": "function",
        "z": "c50bbe8c23efb028",
        "name": "",
        "func": "msg.payload = msg.payload = Math.round(msg.payload.A20*10)/10\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 640,
        "y": 500,
        "wires": [
            [
                "4913ac9eb2034e44"
            ]
        ]
    },
    {
        "id": "4913ac9eb2034e44",
        "type": "ui_gauge",
        "z": "c50bbe8c23efb028",
        "name": "",
        "group": "b4e0c3891df63f73",
        "order": 0,
        "width": 0,
        "height": 0,
        "gtype": "gage",
        "title": "Consumed Energy/Today",
        "label": "kWh",
        "format": "{{value}}",
        "min": 0,
        "max": "2",
        "colors": [
            "#ff7070",
            "#f00000",
            "#811313"
        ],
        "seg1": "",
        "seg2": "",
        "diff": false,
        "className": "",
        "x": 850,
        "y": 500,
        "wires": []
    },
    {
        "id": "5b3de3032f78e203",
        "type": "function",
        "z": "c50bbe8c23efb028",
        "name": "",
        "func": "msg.payload = msg.payload = Math.round(msg.payload.A22*10)/10\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 640,
        "y": 540,
        "wires": [
            [
                "175218b698faf2c8"
            ]
        ]
    },
    {
        "id": "175218b698faf2c8",
        "type": "ui_gauge",
        "z": "c50bbe8c23efb028",
        "name": "",
        "group": "649e58d23e4dde41",
        "order": 0,
        "width": 0,
        "height": 0,
        "gtype": "gage",
        "title": "Consumed Energy/Month",
        "label": "kWh",
        "format": "{{value}}",
        "min": 0,
        "max": "2",
        "colors": [
            "#0400ff",
            "#040080",
            "#040040"
        ],
        "seg1": "",
        "seg2": "",
        "diff": false,
        "className": "",
        "x": 850,
        "y": 540,
        "wires": []
    },
    {
        "id": "c14989dbec16f6ea",
        "type": "function",
        "z": "c50bbe8c23efb028",
        "name": "",
        "func": "msg.payload = Math.round(msg.payload.A24 * 10)/10\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 640,
        "y": 580,
        "wires": [
            [
                "e0bcd79b4d7e57e9"
            ]
        ]
    },
    {
        "id": "e0bcd79b4d7e57e9",
        "type": "ui_gauge",
        "z": "c50bbe8c23efb028",
        "name": "",
        "group": "649e58d23e4dde41",
        "order": 0,
        "width": 0,
        "height": 0,
        "gtype": "gage",
        "title": "Consumed Energy/Year",
        "label": "kWh",
        "format": "{{value}}",
        "min": 0,
        "max": "20",
        "colors": [
            "#ff0004",
            "#800004",
            "#400004"
        ],
        "seg1": "",
        "seg2": "",
        "diff": false,
        "className": "",
        "x": 850,
        "y": 580,
        "wires": []
    },
    {
        "id": "64f7db4f54fe97cb",
        "type": "function",
        "z": "c50bbe8c23efb028",
        "name": "",
        "func": "msg.payload = msg.payload = Math.round(msg.payload.A28*10)/10\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 640,
        "y": 620,
        "wires": [
            [
                "9f1e98a13e54d32a"
            ]
        ]
    },
    {
        "id": "9f1e98a13e54d32a",
        "type": "ui_gauge",
        "z": "c50bbe8c23efb028",
        "name": "",
        "group": "b4e0c3891df63f73",
        "order": 0,
        "width": 0,
        "height": 0,
        "gtype": "gage",
        "title": "Generated Energy/Today",
        "label": "kWh",
        "format": "{{value}}",
        "min": 0,
        "max": "2",
        "colors": [
            "#ff7070",
            "#f00000",
            "#811313"
        ],
        "seg1": "",
        "seg2": "",
        "diff": false,
        "className": "",
        "x": 850,
        "y": 620,
        "wires": []
    },
    {
        "id": "aa02e72b2ac84ffd",
        "type": "function",
        "z": "c50bbe8c23efb028",
        "name": "",
        "func": "msg.payload = msg.payload = Math.round(msg.payload.A30*10/10)\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 640,
        "y": 680,
        "wires": [
            [
                "2e39913a07a2c4df"
            ]
        ]
    },
    {
        "id": "0b85effe64a1b2d6",
        "type": "function",
        "z": "c50bbe8c23efb028",
        "name": "",
        "func": "msg.payload = msg.payload = Math.round(msg.payload.A32*10/10)\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 640,
        "y": 720,
        "wires": [
            [
                "d305f831ef6f502e"
            ]
        ]
    },
    {
        "id": "2e39913a07a2c4df",
        "type": "ui_gauge",
        "z": "c50bbe8c23efb028",
        "name": "",
        "group": "7abb7779e3d4bc3c",
        "order": 4,
        "width": 0,
        "height": 0,
        "gtype": "gage",
        "title": "Generated Energy/Month",
        "label": "kWh",
        "format": "{{value}}",
        "min": 0,
        "max": "4",
        "colors": [
            "#0400ff",
            "#040080",
            "#040040"
        ],
        "seg1": "",
        "seg2": "",
        "diff": false,
        "className": "",
        "x": 850,
        "y": 680,
        "wires": []
    },
    {
        "id": "d305f831ef6f502e",
        "type": "ui_gauge",
        "z": "c50bbe8c23efb028",
        "name": "",
        "group": "7abb7779e3d4bc3c",
        "order": 5,
        "width": 0,
        "height": 0,
        "gtype": "gage",
        "title": "Generated Energy/Year",
        "label": "kWh",
        "format": "{{value}}",
        "min": 0,
        "max": "30",
        "colors": [
            "#ff0004",
            "#800004",
            "#400004"
        ],
        "seg1": "",
        "seg2": "",
        "diff": false,
        "className": "",
        "x": 850,
        "y": 720,
        "wires": []
    },
    {
        "id": "06da6e47ce174595",
        "type": "function",
        "z": "c50bbe8c23efb028",
        "name": "",
        "func": "msg.payload = msg.payload = Math.round(msg.payload.A36*10)/10\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 640,
        "y": 780,
        "wires": [
            [
                "361e0660c9650e3f"
            ]
        ]
    },
    {
        "id": "361e0660c9650e3f",
        "type": "ui_chart",
        "z": "c50bbe8c23efb028",
        "name": "",
        "group": "72208f30aed9593a",
        "order": 3,
        "width": "6",
        "height": "4",
        "label": "Battery Voltage",
        "chartType": "line",
        "legend": "false",
        "xformat": "HH:mm:ss",
        "interpolate": "linear",
        "nodata": "No Data",
        "dot": false,
        "ymin": "0",
        "ymax": "20",
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
        "x": 820,
        "y": 780,
        "wires": [
            []
        ]
    },
    {
        "id": "3a7f8303708ac5a2",
        "type": "function",
        "z": "c50bbe8c23efb028",
        "name": "",
        "func": "msg.payload = msg.payload = Math.round(msg.payload.A37*10)/10\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 640,
        "y": 820,
        "wires": [
            [
                "bc601efb5db84da0"
            ]
        ]
    },
    {
        "id": "bc601efb5db84da0",
        "type": "ui_chart",
        "z": "c50bbe8c23efb028",
        "name": "",
        "group": "72208f30aed9593a",
        "order": 3,
        "width": "6",
        "height": "4",
        "label": "Battery Current",
        "chartType": "line",
        "legend": "false",
        "xformat": "HH:mm:ss",
        "interpolate": "linear",
        "nodata": "No Data",
        "dot": false,
        "ymin": "-3",
        "ymax": "0",
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
        "x": 820,
        "y": 820,
        "wires": [
            []
        ]
    },
    {
        "id": "298af65a43e9620f",
        "type": "function",
        "z": "c50bbe8c23efb028",
        "name": "",
        "func": "msg.payload = msg.payload = Math.round(msg.payload.A12*10)/10\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 640,
        "y": 340,
        "wires": [
            [
                "6d01d6a5993e2903"
            ]
        ]
    },
    {
        "id": "6d01d6a5993e2903",
        "type": "ui_chart",
        "z": "c50bbe8c23efb028",
        "name": "",
        "group": "b4e0c3891df63f73",
        "order": 1,
        "width": "6",
        "height": "4",
        "label": "Device Temperature",
        "chartType": "line",
        "legend": "false",
        "xformat": "HH:mm:ss",
        "interpolate": "linear",
        "nodata": "",
        "dot": false,
        "ymin": "-10",
        "ymax": "50",
        "removeOlder": 1,
        "removeOlderPoints": "144",
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
        "x": 840,
        "y": 340,
        "wires": [
            []
        ]
    },
    {
        "id": "0965fdc21909615c",
        "type": "function",
        "z": "c50bbe8c23efb028",
        "name": "",
        "func": "msg.payload = msg.payload = Math.round(msg.payload.A5*10)/10\nreturn msg;",
        "outputs": 1,
        "timeout": "",
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 640,
        "y": 40,
        "wires": [
            [
                "d9f1c2a084827a6c"
            ]
        ]
    },
    {
        "id": "d9f1c2a084827a6c",
        "type": "ui_chart",
        "z": "c50bbe8c23efb028",
        "name": "",
        "group": "7abb7779e3d4bc3c",
        "order": 3,
        "width": "6",
        "height": "4",
        "label": "PV array Input Power",
        "chartType": "line",
        "legend": "false",
        "xformat": "HH:mm:ss",
        "interpolate": "linear",
        "nodata": "",
        "dot": false,
        "ymin": "0",
        "ymax": "50",
        "removeOlder": 1,
        "removeOlderPoints": "144",
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
        "x": 840,
        "y": 40,
        "wires": [
            []
        ]
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
        "id": "7abb7779e3d4bc3c",
        "type": "ui_group",
        "name": "SOLAR PANNEL DATA",
        "tab": "aadc49ba59317443",
        "order": 2,
        "disp": true,
        "width": "6",
        "collapse": false,
        "className": ""
    },
    {
        "id": "72208f30aed9593a",
        "type": "ui_group",
        "name": "BATTERY DATA",
        "tab": "aadc49ba59317443",
        "order": 4,
        "disp": true,
        "width": "6",
        "collapse": false,
        "className": ""
    },
    {
        "id": "b4e0c3891df63f73",
        "type": "ui_group",
        "name": "REGULATOR AT A GLANCE",
        "tab": "aadc49ba59317443",
        "order": 1,
        "disp": true,
        "width": "6",
        "collapse": false,
        "className": ""
    },
    {
        "id": "649e58d23e4dde41",
        "type": "ui_group",
        "name": "LOAD DATA",
        "tab": "aadc49ba59317443",
        "order": 3,
        "disp": true,
        "width": "6",
        "collapse": false,
        "className": ""
    },
    {
        "id": "aadc49ba59317443",
        "type": "ui_tab",
        "z": "c50bbe8c23efb028",
        "name": "BATTERY CHARGE CONTROLLER",
        "icon": "dashboard",
        "order": 1,
        "disabled": false,
        "hidden": false
    }
]
