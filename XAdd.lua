-- KEYS[1] = stream key
-- ARGV[1] = entry to add
local line = redis.call("xadd", KEYS[1], "*", "data", ARGV[1])
return line