# BatteryManagement

Masurements obtained from the battery management systems
-  `id`: Battery Management ID
   -  Attribute type: **Property**. 
   -  Required
-  `type`: NGSI Entity type. One of : `BatteryManagement`.
   -  Attribute type: **Property**. [Text](https://schema.org/Text)
   -  Required
-  `PVarrayInputVoltage`: PV array input voltage
   -  Attribute type: **Property**. 
   -  Optional
-  `PVarrayInputCurrent`: PV array input current
   -  Attribute type: **Property**. 
   -  Optional
-  `PVarrayInputPower`: PV array input power
   -  Attribute type: **Property**. 
   -  Optional
-  `loadVoltage`: Load voltage
   -  Attribute type: **Property**. 
   -  Optional
-  `loadCurrent`: Load current
   -  Attribute type: **Property**. 
   -  Optional
-  `loadPower`: Load power
   -  Attribute type: **Property**. 
   -  Optional
-  `batteryTemperature`: Battery temperature
   -  Attribute type: **Property**. 
   -  Optional
-  `deviceTemperature`: Device temperature
   -  Attribute type: **Property**. 
   -  Optional
-  `batterySOC`: The remaining capacity percentage of the battery
   -  Attribute type: **Property**. 
   -  Optional
-  `batteryRealRatedVoltage`: Current system rated voltage
   -  Attribute type: **Property**. 
   -  Optional
-  `batteryStatus`: Battery status (16 bits)
   -  Attribute type: **Property**. 
   -  Optional
-  `chargingEquipmentStatus`: Charging equipment status (16 bits)
   -  Attribute type: **Property**. 
   -  Optional
-  `dischargingEquipmentStatus`: Discharging equipment status (16 bits)
   -  Attribute type: **Property**. 
   -  Optional
-  `maximumBatteryVoltageToday`: Maximum battery voltage today
   -  Attribute type: **Property**. 
   -  Optional
-  `minimumBatteryVoltageToday`: Minimum battery voltage today
   -  Attribute type: **Property**. 
   -  Optional
-  `consumedEnergyToday`: Consumed energy today
   -  Attribute type: **Property**. 
   -  Optional
-  `consumedEnergyMonth`: Consumed energy this month
   -  Attribute type: **Property**. 
   -  Optional
-  `consumedEnergyYear`: Consumed energy this year
   -  Attribute type: **Property**. 
   -  Optional
-  `totalConsumedEnergy`: Total consumed energy
   -  Attribute type: **Property**. 
   -  Optional
-  `generatedEnergyToday`: Generated energy today
   -  Attribute type: **Property**. 
   -  Optional
-  `generatedEnergyMonth`: Generated energy this month
   -  Attribute type: **Property**. 
   -  Optional
-  `generatedEnergyYear`: Generated energy this year
   -  Attribute type: **Property**. 
   -  Optional
-  `totalGeneratedEnergy`: Total generated energy
   -  Attribute type: **Property**. 
   -  Optional
-  `batteryVoltage`: Battery voltage
   -  Attribute type: **Property**. 
   -  Optional
-  `batteryCurrent`: PV array input power
   -  Attribute type: **Property**. 
   -  Optional
-  `refControlBoard`: Reference of the -Terrain- to which this sensor belongs.
   -  Attribute type: **Relationship**. 
   -  Optional



## Examples

### OK


#### Key-Values Pairs

```json
[
    {
        "id": "urn:ngsi-ld:BatteryManagement:EPEVERtrace01",
        "type": "BatteryManagement",
        "batteryVoltage": {
            "value": 11.95,
            "unirCode": "VLT",
            "observedAt": "2022-08-12T07:58:07+00:00Z"
        },
        "refControlBoard": "urn:ngsi-ld:ControlBoard:CTRLBRD01",
        "@context": [
            "https://uri.etsi.org/ngsi-ld/v1/ngsi-ld-core-context.jsonld",
            "https://raw.githubusercontent.com/jpcoelhoATipbDOTpt/MAN4HEALTH/main/DataModel/Hardware/BatteryManagement/Context/context-keyvalues.jsonld"
        ]
    }
]
```

#### Normalized NGSI-LD

```json
[
    {
        "id": "urn:ngsi-ld:BatteryManagement:EPEVERtracerP01",
        "type": "BatteryManagement",
        "batteryVoltage": {
            "type": "Property",
            "value": 11.95,
            "unirCode": "VLT",
            "observedAt": "2022-08-12T07:58:07+00:00Z"
        },
        "refControlBoard": {
            "type": "Relationship",
            "object": "urn:ngsi-ld:ControlBoard:CTRLBRD01"
        },
        "@context": [
            "https://uri.etsi.org/ngsi-ld/v1/ngsi-ld-core-context.jsonld",
            "https://raw.githubusercontent.com/jpcoelhoATipbDOTpt/MAN4HEALTH/main/DataModel/Hardware/BatteryManagement/Context/context-keyvalues.jsonld"
        ]
    }
]
```
