# Terrain

Entity that represent a farmland
-  `id`: Unique identifier of the entity
   -  Attribute type: **Property**. 
   -  Required
-  `type`: NGSI entity type for -Terrain-. One of : `Terrain`.
   -  Attribute type: **Property**. 
   -  Required
-  `terrainSpecs`: Description of relevant terrain characteristics
   -  Attribute type: **Property**. 
   -  Optional
-  `address`: The owner address
   -  Attribute type: **Property**. 
   -  Optional



## Examples

### OK


#### Key-Values Pairs

```json
[
    {
        "id": "urn:ngsi-ld:Terrain:T001",
        "type": "Terrain",
        "terrainSpecs": {
            "location": {
                "coordinates": [
                    41.488698,
                    -7.248216
                ],
                "type": "Point"
            },
            "nearestLocation": "Mirandela",
            "terrainArea": 1.5,
            "aditionalNotes": "Terreno perto de Suçães, Mirandela, com plantação de oliveiras"
        },
        "ownerName": "Nome do dono do terreno",
        "specification": "Terreno localizado perto de Mirandela",
        "address": {
            "ownerName": "---",
            "streetAddress": "---",
            "postalCode": "XXXX-XXX",
            "addressLocalitty": "Mirandela",
            "addressCountry": "Portugal",
            "telephone": "(+351) 930 000 000",
            "email": "exemplo@mail.pt"
        },
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
        "id": "urn:ngsi-ld:Terrain:T001",
        "type": "Terrain",
        "terrainSpecs": {
            "type": "Property",
            "value": {
                "location": {
                    "type": "GeoProperty",
                    "value": {
                        "type": "Point",
                        "coordinates": [
                            41.488698,
                            -7.248216
                        ]
                    }
                },
                "nearestLocation": {
                    "type": "Property",
                    "value": "Mirandela"
                },
                "terrainArea": {
                    "type": "Property",
                    "value": 2.5
                },
                "aditionalNotes": {
                    "type": "Property",
                    "value": "Terreno em Suçães com plantação de oliveiras"
                }
            }
        },
        "address": {
            "type": "Property",
            "value": {
                "ownerName": {
                    "type": "Property",
                    "value": "---"
                },
                "streetAddress": {
                    "type": "Property",
                    "value": "---"
                },
                "postalCode": {
                    "type": "Property",
                    "value": "XXXX-XXX"
                },
                "addressLocality": {
                    "type": "Property",
                    "value": "---"
                },
                "addressCountry": {
                    "type": "Property",
                    "value": "Portugal"
                },
                "telephone": {
                    "type": "Property",
                    "value": "(+351) 930 000 000"
                },
                "email": {
                    "type": "Property",
                    "value": "exemplo@mail.pt"
                }
            }
        },
        "@context": [
            "https://uri.etsi.org/ngsi-ld/v1/ngsi-ld-core-context.jsonld",
            "https://raw.githubusercontent.com/jpcoelhoATipbDOTpt/MAN4HEALTH/main/DataModel/Terrain/Context/context-normalized.jsonld"
        ]
    }
]
```
