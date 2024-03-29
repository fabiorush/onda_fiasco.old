#pragma once

#include <l4/sys/types.h>

// To generate the kernel version:
// perl -p -e 's/l4_uint(\d+)_t/Unsigned$1/;s/^#inc.+/#include "types.h"/' koptions-def.h

namespace L4_kernel_options
{
  enum Flags
  {
    F_wait              = 1 << 0,
    F_serial_esc        = 1 << 1,
    F_noserial          = 1 << 2,
    F_noscreen          = 1 << 3,
    F_esc               = 1 << 4,
    F_nojdb             = 1 << 5,
    F_nokdb             = 1 << 6,
    F_nohlt             = 1 << 7,
    F_apic              = 1 << 8,
    F_loadcnt           = 1 << 9,
    F_watchdog          = 1 << 10,
    F_rotext            = 1 << 11,
    F_profile           = 1 << 12,
    F_irq0              = 1 << 13,
    F_profstart         = 1 << 14,
    F_nosfn             = 1 << 15,
    F_jdb_never_stop    = 1 << 16,

    F_kmemsize          = 1 << 17,
    F_tbuf_entries      = 1 << 18,
    F_out_buf           = 1 << 19,
    F_uart_baud         = 1 << 20,
    F_uart_base         = 1 << 21,
    F_uart_irq          = 1 << 22,

    F_jdb_cmd           = 1 << 23,
  };

  enum
  {
    Magic = 0x4C344B43,
  };

  enum Uart_types
  {
    Uart_type_invalid = 0,
    Uart_type_ioport  = 1,
    Uart_type_mmio    = 2,
  };

  struct Uart
  {
    l4_uint32_t  access_type;  ///< Accesstype of UART: unset, MMIO or ports
    l4_uint32_t  baud;         ///< Baud rate
    l4_uint32_t  irqno;        ///< (Receive) IRQ
    l4_uint64_t  base_address; ///< Start address of UART
  } __attribute__((packed));

  struct Options
  {
    l4_uint32_t  magic;            ///< Magic value
    l4_uint32_t  version;          ///< Version of this structure

    l4_uint32_t  flags;            ///< Option flags

    l4_uint32_t  kmemsize;         ///< Wanted kernel memory size in KiB

    Uart uart;                     ///< Kernel UART

    char         jdb_cmd[128];
    l4_uint32_t  tbuf_entries;
    l4_uint32_t  out_buf;

    l4_uint32_t  opt(Flags flag) const { return flags & flag; }

  } __attribute__((packed));
};
