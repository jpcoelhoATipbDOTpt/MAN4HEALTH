|Var         |Default|Description|
|ORIONLD_PORT|1026|Port to receive new connections.|
|ORIONLD_FOREGROUND|false|Don't start as daemon.|
|ORIONLD_LOCALIP|0.0.0.0|IP to receive new connections.|
|ORIONLD_PID_PATH|/tmp/contextBroker.pid|Pid file path.|
|ORIONLD_MONGO_HOST|localhost|Mongo-DB database host.|
|ORIONLD_MONGO_REPLICA_SET||Name of the replica-set, if usd.|
|ORIONLD_MONGO_USER||Username for connecting mongo-db.|
|ORIONLD_MONGO_PASSWORD||Password for connecting mongo-db.|
|ORIONLD_MONGO_DB|orion|Name of the database to be used inside mongo-db.|
|ORIONLD_MONGO_TIMEOUT|10000|Timeout in milliseconds for connections to the replica set (ignored in the case of not using replica set).|
|ORIONLD_MONGO_POOL_SIZE|10|Size of the mongo-db connection pool.|
|ORIONLD_MONGO_WRITE_CONCERN|1|Write concern (0:unacknowledged, 1:acknowledged) to be used with mongo-db.|
|ORIONLD_MONGO_ID_INDEX|false|Should an index on _id.id be automatically set.|
|ORIONLD_USEIPV4|false|Use IP-V4 only.|
|ORIONLD_USEIPV6|false|Use IP-V6 only.|
|ORIONLD_HARAKIRI|false|Commits harakiri on request.|
|ORIONLD_HTTPS|false|Use the https 'protocol'.|
|ORIONLD_HTTPS_KEYFILE||Private server key file (for https).|
|ORIONLD_HTTPS_CERTFILE||Certificate key file (for https).|
|ORIONLD_MULTI_SERVICE|false|Enable multi-tenancy.|
|ORIONLD_HTTP_TIMEOUT|-1|Timeout in milliseconds for forwards and notifications.|
|ORIONLD_REQ_TIMEOUT|0|Connection timeout for REST requests (in seconds).|
|ORIONLD_MUTEX_POLICY|transient|Mutex policy (none/read/write/all).|
|ORIONLD_CORS_ALLOWED_ORIGIN||Enable Cross-Origin Resource Sharing with allowed origin. Use '__ALL' for any.|
|ORIONLD_CORS_MAX_AGE|86400|Maximum time in seconds preflight requests are allowed to be cached.|
|ORIONLD_CPR_FORWARD_LIMIT|1000|Maximum number of forwarded requests to Context Providers for a single client request.|
|ORIONLD_SUBCACHE_IVAL|0|Interval in seconds between calls to Subscription Cache refresh (0: no refresh).|
|ORIONLD_NOCACHE|false|Disable subscription cache for lookups.|
|ORIONLD_CONN_MEMORY|64|Maximum memory size per connection (in kilobytes).|
|ORIONLD_MAX_CONN|1020|Maximum number of simultaneous connections.|
|ORIONLD_TRQ_POOL_SIZE|0|Size of thread pool for incoming connections.|
|ORIONLD_NOTIF_MODE|transient|Notification mode (persistent|
|ORIONLD_DROP_NOTIF|false|Simulate notifications instead of actual sending them (only for testing).|
|ORIONLD_STAT_COUNTERS|false|Enable request/notification counters statistics.|
|ORIONLD_STAT_SEM_WAIT|false|Enable semaphore waiting time statistics.|
|ORIONLD_STAT_TIMING|false|Enable request-time-measuring statistics.|
|ORIONLD_STAT_NOTIF_QUEUE|false|Enable thread pool notifications queue statistics.|
|ORIONLD_LOG_SUMMARY_PERIOD|0|Log summary period in seconds (defaults to 0, meaning 'off').|
|ORIONLD_RELOG_ALARMS|false|Log messages for existing alarms beyond the raising alarm log message itself|
|ORIONLD_CHECK_ID_V1|false|Additional checks for id fields in the NGSIv1 API.|
|ORIONLD_DISABLE_CUSTOM_NOTIF|false|Disable NGSIv2 custom notifications.|
|ORIONLD_LOG_FOR_HUMANS|false|Human readable logs.|
|ORIONLD_DISABLE_FILE_LOG|false|Disable logging into a file|
|ORIONLD_DISABLE_METRICS|false|Turn off the 'metrics' feature.|
|ORIONLD_INSECURE_NOTIF|false|Allow HTTPS notifications to peers which certificate cannot be authenticated with known CA certificates.|
|ORIONLD_NGSIV1_AUTOCAST|false|Automatic cast for number, booleans and dates in NGSIv1 update/create attribute operations.|
|ORIONLD_CONTEXT_DOWNLOAD_TIMEOUT|5000|Timeout in milliseconds for downloading of contexts.|
|ORIONLD_CONTEXT_DOWNLOAD_ATTEMPTS|3|Number of attempts for downloading of contexts.|
|ORIONLD_TROE|false|Enable TRoE - temporal representation of entities.|
|ORIONLD_TROE_HOST|localhost|Host for troe database db server.|
|ORIONLD_TROE_PORT|5432|Port for troe database db server.|
|ORIONLD_TROE_USER|postgres|Username for troe database db server.|
|ORIONLD_TROE_PWD|password|Password for troe database db server.|
|ORIONLD_TROE_POOL_SIZE|10|Port to receive new connections.|
|ORIONLD_TMP_TRACES|`true|Port to receive new connections.|
|ORIONLD_SOCKET_SERVICE|false|Enable the socket service - accept connections via a normal TCP socket.|
|ORIONLD_SOCKET_SERVICE_PORT|1027|Size of the connection pool for TRoE Postgres database connections.|
|ORIONLD_FORWARDING|false|Turn on forwarding.|
|ORIONLD_NO_NOTIFY_FALSE_UPDATE|false|Turn off notifications on non-updates.|
|ORIONLD_NOSWAP|false|Disable swapping.|
