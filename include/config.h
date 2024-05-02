#ifndef DYNAMIXEL_CONFIG_H_
#define DYNAMIXEL_CONFIG_H_


#define ENABLE_ACTUATOR_AX              1
#define ENABLE_ACTUATOR_DX              0
#define ENABLE_ACTUATOR_RX              0
#define ENABLE_ACTUATOR_EX              0
#define ENABLE_ACTUATOR_MX12W           1
#define ENABLE_ACTUATOR_MX28            1
#define ENABLE_ACTUATOR_MX64            1
#define ENABLE_ACTUATOR_MX106           1

#define ENABLE_ACTUATOR_MX28_PROTOCOL2  1
#define ENABLE_ACTUATOR_MX64_PROTOCOL2  1
#define ENABLE_ACTUATOR_MX106_PROTOCOL2 1

#define ENABLE_ACTUATOR_XL320           1
#define ENABLE_ACTUATOR_XL330           1
#define ENABLE_ACTUATOR_XC330           1
#define ENABLE_ACTUATOR_XL430           1  // includes 2XL430
#define ENABLE_ACTUATOR_XC430           1  // includes 2XC430
#define ENABLE_ACTUATOR_XM430           1
#define ENABLE_ACTUATOR_XH430           1  // includes V lineup
#define ENABLE_ACTUATOR_XD430           1
#define ENABLE_ACTUATOR_XM540           1
#define ENABLE_ACTUATOR_XH540           1  // includes V lineup
#define ENABLE_ACTUATOR_XD540           1
#define ENABLE_ACTUATOR_XW430           1
#define ENABLE_ACTUATOR_XW540           1

#define ENABLE_ACTUATOR_PRO_R           1
#define ENABLE_ACTUATOR_PRO_RA          1
#define ENABLE_ACTUATOR_PRO_PLUS        1

#define DXL_BYTE_STUFF_SAFE_CNT         8

#define DEFAULT_DXL_BUF_LENGTH       1024

#if (DEFAULT_DXL_BUF_LENGTH > 0xFFFF)
#error "\r\nError : DEFAULT_DXL_BUF_LENGTH is OVERFLOW! This must be a 16 bit range."
#endif



#define DXL_MAX_NODE                   18
#define DXL_MAX_NODE_BUFFER_SIZE       18

#define DXL_BUF_LENGTH (DXL_MAX_NODE*DXL_MAX_NODE_BUFFER_SIZE + 11) // 11 = Header(3)+Reserved(1)+ID(1)+Length(2)+Instruction(1)+Error(1)+crc(2)
#if (DXL_BUF_LENGTH > DEFAULT_DXL_BUF_LENGTH)
#undef DEFAULT_DXL_BUF_LENGTH
#define DEFAULT_DXL_BUF_LENGTH  DXL_BUF_LENGTH
#endif

#if (DXL_MAX_NODE > 253)
#error "\r\nError : DXL_MAX_NODE is OVERFLOW! This should be less or equal than 253 by the protocol."
#endif
#if (DXL_MAX_NODE_BUFFER_SIZE > 0xFF)
#error "\r\nError : DXL_MAX_NODE_BUFFER_SIZE is OVERFLOW! This must be a 8 bit range."
#endif
#if (DXL_BUF_LENGTH > 0xFFFF)
#error "\r\nError : DXL_BUF_LENGTH is OVERFLOW! This must be a 16 bit range."
#endif

#if !defined(PROGMEM)
  #define PROGMEM
#endif

#if !defined(pgm_read_word_near)
  #define pgm_read_word_near(x) (*(uint16_t*)(x))
#endif

#endif /* DYNAMIXEL_CONFIG_H_ */