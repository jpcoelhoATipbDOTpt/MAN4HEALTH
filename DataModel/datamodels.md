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



# Device

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
-  `specification`: -Device- description
   -  Attribute type: **Property**. 
   -  Optional
-  `hardware`: Describes the -Device- hardware
   -  Attribute type: **Property**. 
   -  Optional
-  `refParcel`: The -Parcel- to which the -Device- is associated
   -  Attribute type: **Relationship**. 
   -  Required



# moisture

Defines a given humidity sensor to be used in a -Device-
-  `id`: Sensor identifier
   -  Attribute type: **Property**. 
   -  Required
-  `type`: NGSI Entity type. It has to be moisture. One of : `moisture`.
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



# temperature

Defines a given temperature sensor to be used in a -Device-
-  `id`: Sensor identifier
   -  Attribute type: **Property**. 
   -  Required
-  `type`: NGSI Entity type. It has to be temperature. One of : `temperature`.
   -  Attribute type: **Property**. 
   -  Required
-  `measuringMedium`: Define tthe medium from where the measurement is taken
   -  Attribute type: **Property**. [Text](https://schema.org/Text)
   -  Optional
-  `dephtOrAltitude`: Defines the depth or altitude at which the measurement is taken (in centimeters)
   -  Attribute type: **Property**. 
   -  Optional
-  `measuredValue`: Measured temperature (in degrees Celsius)
   -  Attribute type: **Property**. 
   -  Optional
-  `dateObserved`: The date and time of this observation as defined by RFC 3339.
   -  Attribute type: **Property**. [DateTime](https://schema.org/DateTime)
   -  Optional
-  `refDevice`: Reference of the -Device- to which this sensor belongs.
   -  Attribute type: **Relationship**. 
   -  Required



# battery

Defines the battery status of a given -Device-
-  `id`: Battery identifier
   -  Attribute type: **Property**. 
   -  Required
-  `type`: NGSI Entity type. It has to be battery. One of : `battery`.
   -  Attribute type: **Property**. 
   -  Required
-  `batteryLevel`: Device battery level. It must be equal to 1.0 when battery is full. 0.0 when battery is empty. -1 when cannot be determined.
   -  Attribute type: **Property**. [Number](https://schema.org/Number)
   -  Optional
-  `dateObserved`: The date and time of this observation as defined by RFC 3339.
   -  Attribute type: **Property**. [DateTime](https://schema.org/DateTime)
   -  Optional
-  `batteryDetails`: Technical details about the batteries
   -  Attribute type: **Property**. 
   -  Optional
-  `refDevice`: Reference of the -Device- to which this sensor belongs.
   -  Attribute type: **Relationship**. 
   -  Required



# lora

Defines the LoRA transceiver and protocol associated to a given -Device-
-  `id`: LoR transceiver identifier
   -  Attribute type: **Property**. 
   -  Required
-  `type`: NGSI Entity type. It has to be lora. One of : `lora`.
   -  Attribute type: **Property**. 
   -  Required
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


