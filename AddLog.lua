-- KEYS[1] = log line table
-- KEYS[2] = log zset table
-- ARGV[1] = entry to add
local line = redis.call("incr", KEYS[1])
redis.call("zadd", KEYS[2], line, ARGV[1])
return line