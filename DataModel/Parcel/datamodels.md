# Parcel

Entity that represent a parcel within a terrain
-  `id`: Unique identifier of the entity
   -  Attribute type: **Property**. 
   -  Required
-  `location`: Geogrphic location of a -Parcel- in one of two possible formats: point or polygon
   -  Attribute type: **Geoproperty**. 
   -  Required
-  `type`: NGSI entity type for -Parcel-.. One of : `Parcel`.
   -  Attribute type: **Property**. 
   -  Required
-  `specification`: Description of relevant parcel characteristics
   -  Attribute type: **Property**. 
   -  Optional
-  `refDevices`: List of entities of type -Device- associated to the current -Parcel-. Topological integrity must exist between the device and parcel locations since a -Device. must be within a -Parcel-.
   -  Attribute type: **Relationship**. 
   -  Optional
-  `refExperimental`: List of entities of type -Experimental- associated to the current -Parcel-.
   -  Attribute type: **Relationship**. 
   -  Optional
-  `refTerrain`: Reference to the -Terrain- that this -Parcel- belongs to.
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
        "refDevices": [
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
        "refDevices": [
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
