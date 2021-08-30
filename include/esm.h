struct
{
    char type[4];
    uint16_t size;
    BYTE* data; // encoded as 'size' BYTES
} Field;

struct
{
    char     type[4]
    uint32_t data_size; // size of data field
    uint32_t flags; // size of data field
    uint32_t identifier; // Record (form) identifier
    uint16_t timestamp;
    uint16_t version_control_info;
    uint16_t internal_version;
    uint16_t unknown;
    Field*   fields;  // encoded as 'data_size' number of BYTES
} Record;


struct
{
    char     type[4] = {"GRUP"}; // always
    uint32_t size; // size of the entire group, including the group header
    BYTE     label[4];
    int32_t  group_type;
    uint16_t timestamtp;
    uint16_t version_control_info;
    uint32_t unknown;
    Record*  records;
} Group;


