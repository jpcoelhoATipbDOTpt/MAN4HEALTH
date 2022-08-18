# Device

An IoT device that will be used to get and relay measurement values from sensors
-  `id`: Unique identifier of the entity
   -  Attribute type: **Property**. 
   -  Required
-  `type`: NGSI Entity type. It has to be Device. One of : `Device`.
   -  Attribute type: **Property**. 
   -  Required
-  `dateInstalled`: A timestamp which denotes when the - Device- was deployed
   -  Attribute type: **Property**. [DateTime](https://schema.org/DateTime)
   -  Optional
-  `specification`: -Device- description
   -  Attribute type: **Property**. 
   -  Optional
-  `hardware`: Describes the -Device- hardware
   -  Attribute type: **Property**. 
   -  Optional
-  `refParcel`: The -Parcel- to which the -Device- is associated
   -  Attribute type: **Relationship**. 
   -  Required



## Examples

### OK


#### Key-Values Pairs

```json
[
    {
        "id": "urn:Terrain:Parcel:Device:QwW4rF3A",
        "type": "Device",
        "dateInstalled": "2022-08-12T07:58:07+00:00",
        "name": "Nó IoT em a1",
        "hardware": {
            "CPU": "ATMega328",
            "hardwareVersion": "1.0",
            "firmwareVersion": "1.5",
            "refTransceiver": [
                "uri:device:hardware:transceiver:lora:A8X9df4",
                "uri:device:transceiver:gnss:W1ad45F"
            ],
            "refPowerSupply": [
                "uri:device:hardware:battery:A01T54gH"
            ],
            "refSensors": [
                "uri:device:hardware:sensors:temperature:X9dfGg8",
                "uri:device:hardware:sensors:moisture:MyU7IO"
            ]
        },
        "refParcel": "urn:ngsi-ld:Terrain:Parcel:MDLA4172",
        "@context": [
            "https://uri.etsi.org/ngsi-ld/v1/ngsi-ld-core-context.jsonld",
            "https://raw.githubusercontent.com/jpcoelhoATipbDOTpt/MAN4HEALTH/main/DataModel/Device/Context/context-keyvalues.jsonld"
        ]
    }
]
```

#### Normalized NGSI-LD

```json
[
    {
        "id": "urn:Terrain:Parcel:Device:QwW4rF3A",
        "type": "Device",
        "dateInstalled": {
            "type": "Property",
            "value": {
                "@type": "DateTime",
                "@value": "2022-08-12T07:58:07+00:00"
            }
        },
        "name": {
            "type": "Property",
            "value": "Nó IoT em a1"
        },
        "hardware": {
            "CPU": {},
            "hardwareVersion": {},
            "firmwareVersion": {},
            "refTransceiver": {
                "type": "Relationship",
                "object": [
                    "uri:device:hardware:transceiver:lora:A8X9df4",
                    "uri:device:transceiver:gnss:W1ad45F"
                ]
            },
            "refPowerSupply": {
                "type": "Relationship",
                "object": [
                    "uri:device:hardware:battery:A01T54gH"
                ]
            },
            "refSensors": {
                "type": "Relationship",
                "object": [
                    "uri:device:hardware:sensors:temperature:X9dfGg8",
                    "uri:device:hardware:sensors:moisture:MyU7IO"
                ]
            }
        },
        "refParcel": {
            "type": "Relationship",
            "object": "urn:ngsi-ld:Terrain:Parcel:MDLA4172"
        },
        "@context": [
            "https://uri.etsi.org/ngsi-ld/v1/ngsi-ld-core-context.jsonld",
            "https://raw.githubusercontent.com/jpcoelhoATipbDOTpt/MAN4HEALTH/main/DataModel/Device/Context/context-normalized.jsonld"
        ]
    }
]
```
