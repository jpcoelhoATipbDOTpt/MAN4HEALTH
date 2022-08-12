# moisture

Defines a given humidity sensor to be used in a -Device-
-  `id`: Sensor identifier
   -  Attribute type: **Property**. 
   -  Required
-  `measuringMedium`: Define the medium from where the measurement is taken
   -  Attribute type: **Property**. [Text](https://schema.org/Text)
   -  Optional
-  `dephtOrAltitude`: Defines the depth or altitude at which the measurement is taken (in centimeters)
   -  Attribute type: **Property**. 
   -  Optional
-  `measuredValue`: Measured humidity (in percentage)
   -  Attribute type: **Property**. 
   -  Optional
-  `dateObserved`: The date and time of this observation as defined by RFC 3339
   -  Attribute type: **Property**. [DateTime](https://schema.org/DateTime)
   -  Optional
-  `refDevice`: Reference of the -Device- to which this sensor belongs.
   -  Attribute type: **Relationship**. 
   -  Required



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
