# Terrain

Entity that represent a farmland
-  `id`: Unique identifier of the entity
   -  Attribute type: **Property**. 
   -  Required
-  `location`: Geographic location of a -Terrain- in point or polygon format
   -  Attribute type: **Geoproperty**. 
   -  Required
-  `type`: NGSI entity type for -Terrain-. One of : `Terrain`.
   -  Attribute type: **Property**. 
   -  Required
-  `ownerName`: Owner name
   -  Attribute type: **Property**. 
   -  Optional
-  `specification`: Description of relevant terrain characteristics
   -  Attribute type: **Property**. 
   -  Optional



## Examples

### OK


#### Key-Values Pairs

```json
[
    {
        "id": "urn:ngsi-ld:Terrain:AWQ2FrqwT",
        "type": "Terrain",
        "location": {
            "coordinates": [
                41.488698,
                -7.248216
            ],
            "type": "Point"
        },
        "ownerName": "Nome do dono do terreno",
        "specification": "Terreno localizado perto de Mirandela",
        "@context": [
            "https://uri.etsi.org/ngsi-ld/v1/ngsi-ld-core-context.jsonld",
            "https://raw.githubusercontent.com/jpcoelhoATipbDOTpt/MAN4HEALTH/main/DataModel/Terrain/Context/context-keyvalues.jsonld"
        ]
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
            "type": "geo:json",
            "value": {
                "type": "Point",
                "coordinates": [
                    41.488698,
                    -7.248216
                ]
            }
        },
        "ownerName": {
            "type": "Property",
            "value": "Nome do dono do terreno"
        },
        "specification": {
            "type": "Property",
            "value": "Terreno localizado perto de Mirandela"
        },
        "@context": [
            "https://uri.etsi.org/ngsi-ld/v1/ngsi-ld-core-context.jsonld",
            "https://raw.githubusercontent.com/jpcoelhoATipbDOTpt/MAN4HEALTH/main/DataModel/Terrain/Context/context-normalized.jsonld"
        ]
    }
]
```
