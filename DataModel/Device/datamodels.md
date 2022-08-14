# Parcel

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
-  `name`: The name of this -Device-
   -  Attribute type: **Property**. 
   -  Optional
-  `hardware`: Describes the -Device- hardware
   -  Attribute type: **Property**. 
   -  Optional
-  `refParcel`: The -Parcel- to which the -Device- is associated
   -  Attribute type: **Relationship**. 
   -  Optional



## Examples

### OK


#### Key-Values Pairs

```json
[
    {
        "id": "urn:ngsi-ld:Parcel:a1",
        "type": "Parcel",
        "location": {
            "type": "Point",
            "coordinates": [
                41.488698,
                -7.248216
            ]
        },
        "specification": "Parcela com coordenada A1 associada ao terreno localizado em Mirandela",
        "refDevice": [
            "urn:ngsi-ld:Device:S8Q858P868W8P8p8l8Q",
            "urn:ngsi-ld:Device:k8w8C8O868Y8N838889"
        ],
        "refExperimental": [
            "urn:ngsi-ld:Experimental:C8g8B8R8j818V8F8p8n"
        ],
        "refTerrain": "urn:ngsi-ld:Terrain:MDLA4172"
    }
]
```

#### Normalized NGSI-LD

```json
[
    {
        "id": "urn:ngsi-ld:Parcel:a1",
        "type": "Parcel",
        "location": {
            "coordinates": [
                41.488698,
                -7.248216
            ],
            "type": "Point"
        },
        "specification": "Parcela com coordenada A1 associada ao terreno localizado em Mirandela",
        "refDevice": [
            "urn:ngsi-ld:Device:S8Q858P868W8P8p8l8Q",
            "urn:ngsi-ld:Device:k8w8C8O868Y8N838889"
        ],
        "refExperimental": [
            "urn:ngsi-ld:Experimental:C8g8B8R8j818V8F8p8n"
        ],
        "refTerrain": "urn:ngsi-ld:Terrain:MDLA4172",
        "@context": [
            "https://uri.etsi.org/ngsi-ld/v1/ngsi-ld-core-context.jsonld",
            "https://raw.githubusercontent.com/jpcoelhoATipbDOTpt/MAN4HEALTH/main/DataModel/Parcel/Context/context-normalized.jsonld"
        ]
    }
]
```
