# Preface

Clients and server have a database that contain data. Both side share the same
data structure.

# dir

This table contains the directory structure. Directory #0 is the root

* dir_id
* parent_dir_id
* name
* chmod
* stamp

# dir_whiteout

* dir_id
* stamp

# file

* file_id
* dir_id
* name
* chmod
* stamp

# file_block

* file_id
* offset
* block_hash
* stamp

# file_whiteout

* file_id
* stamp
