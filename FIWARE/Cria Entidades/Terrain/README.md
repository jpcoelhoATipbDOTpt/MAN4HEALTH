```console
curl --location --request POST 'http://localhost:1026/ngsi-ld/v1/entities/' \
--header 'Content-Type: application/ld+json' \
--header 'Accept: application/ld+json' \
--header 'Fiware-Service: man4health' \
--header 'Fiware-ServicePath: terrain' \
--data-raw '{
  "id": "urn:ngsi-ld:Terrain:T001",
  
  "type": "Terrain",
  
  "location": {
    "type": "GeoProperty",
    "value": {
      "type": "Point",
      "coordinates": [41.488698, -7.248216]
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

}'
```
