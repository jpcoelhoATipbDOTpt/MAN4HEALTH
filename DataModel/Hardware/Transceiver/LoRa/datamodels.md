# lora

Defines the LoRA transceiver and protocol associated to a given -Device-
-  `id`: LoR transceiver identifier
   -  Attribute type: **Property**. 
   -  Required
-  `type`: NGSI Entity type. It has to be lora. One of : `lora`.
   -  Attribute type: **Property**. 
   -  Optional
-  `rssi`: Indicate the value of the RSSI
   -  Attribute type: **Property**. 
   -  Optional
-  `abp`: ABP credentials
   -  Attribute type: **Property**. 
   -  Optional
-  `refDevice`: Reference of the -Device- to which this transceiver belongs.
   -  Attribute type: **Relationship**. 
   -  Required



## Examples

### OK


#### Key-Values Pairs

```json
[
    {
        "id": "urn:device:hardware:transceiver:lora:XpX5DdfR5",
        "type": "lora",
        "rssi": {
            "measuredValue": -85,
            "dateObserved": "2022-08-12T07:58:07+00:00"
        },
        "abp": {
            "NwkSkey": "{0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C}",
            "AppSkey": "{0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C}",
            "DevAddr": "{0x03, 0xFF, 0x00, 0x01}"
        },
        "refDevice": "urn:ngsi-ld:Device:S8Q858P868W8P8p8l8Q",
        "@context": [
            "https://uri.etsi.org/ngsi-ld/v1/ngsi-ld-core-context.jsonld",
            "https://raw.githubusercontent.com/jpcoelhoATipbDOTpt/MAN4HEALTH/main/DataModel/Hardware/Transceivers/LoRa/Context/context-keyvalues.jsonld"
        ]
    }
]
```

#### Normalized NGSI-LD

```json
[
    null
]
```
