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
    "{\n  \"id\": \"urn:ngsi-ld:Parcel:a1\",\n  \n  \"type\": \"Parcel\",\n  \n  \"location\": {\n    \"type\": \"geo:json\",\n    \"value\": {\n      \"type\": \"Point\",\n      \"coordinates\": [41.488698, -7.248216]\n    }\n  }, \n\n  \"ownerName\": {\n    \"type\": \"Property\",\n    \"value\": \"Nome do dono do terreno\"\"\n  },\n\n  \"specification\": {\n    \"type\": \"Property\",\n    \"value\": \"Terreno localizado perto de Mirandela\"\n  },\n \n  \"@context\": [\n  \"https://uri.etsi.org/ngsi-ld/v1/ngsi-ld-core-context.jsonld\",\n  \"https://raw.githubusercontent.com/jpcoelhoATipbDOTpt/MAN4HEALTH/main/DataModel/Terrain/Context/context-normalized.jsonld\"\n  ]\n\n}\n"
]
```
