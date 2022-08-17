# Parcel

Entity that represent a parcel within a terrain
-  `id`: Unique identifier of the entity
   -  Attribute type: **Property**. 
   -  Required
-  `location`: Geographic location of a -Parcel- as a point or polygon
   -  Attribute type: **Geoproperty**. 
   -  Optional
-  `type`: NGSI entity type for -Parcel-. One of : `Parcel`.
   -  Attribute type: **Property**. 
   -  Required
-  `specification`: Description of relevant parcel characteristics
   -  Attribute type: **Property**. 
   -  Optional
-  `refTerrain`: Reference to the -Terrain- that this -Parcel- belongs to.
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
        "refTerrain": {
            "type": "Relationship",
            "value": "urn:ngsi-ld:Terrain:MDLA4172"
        },
        "@context": [
            "https://uri.etsi.org/ngsi-ld/v1/ngsi-ld-core-context.jsonld",
            "https://raw.githubusercontent.com/jpcoelhoATipbDOTpt/MAN4HEALTH/main/DataModel/Parcel/Context/context-keyvalues.jsonld"
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
        "specification": {
            "type": "Property",
            "value": "Parcela com coordenada A1 associada ao terreno localizado em Mirandela"
        },
        "refTerrain": {
            "type": "Relationship",
            "value": "urn:ngsi-ld:Terrain:MDLA4172"
        },
        "@context": [
            "https://uri.etsi.org/ngsi-ld/v1/ngsi-ld-core-context.jsonld",
            "https://raw.githubusercontent.com/jpcoelhoATipbDOTpt/MAN4HEALTH/main/DataModel/Parcel/Context/context-normalized.jsonld"
        ]
    }
]
```
