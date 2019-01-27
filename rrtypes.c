#include "dnsextlang.h"
static dnsextlang_field t0001_fields[1] = {
	{ del_ftype_A, 0, { NULL }, NULL, "addr"
	, "IPv4 address" }
};
static dnsextlang_stanza t0001 = {
	"A", 1, (del_option_I),
	"a host address [RFC1035]",
	1, t0001_fields
};
static dnsextlang_field t0002_fields[1] = {
	{ del_ftype_N, (del_qual_C), { NULL }, NULL, "host"
	, "Host name" }
};
static dnsextlang_stanza t0002 = {
	"NS", 2, (del_option_A),
	"an authoritative name server [RFC1035]",
	1, t0002_fields
};
static dnsextlang_field t0003_fields[1] = {
	{ del_ftype_N, (del_qual_C), { NULL }, NULL, "host"
	, "Host name" }
};
static dnsextlang_stanza t0003 = {
	"MD", 3, (del_option_A|del_option_O),
	"a mail destination (OBSOLETE - use MX) [RFC1035]",
	1, t0003_fields
};
static dnsextlang_field t0004_fields[1] = {
	{ del_ftype_N, (del_qual_C), { NULL }, NULL, "host"
	, "Host name" }
};
static dnsextlang_stanza t0004 = {
	"MF", 4, (del_option_A|del_option_O),
	"a mail forwarder (OBSOLETE - use MX) [RFC1035]",
	1, t0004_fields
};
static dnsextlang_field t0005_fields[1] = {
	{ del_ftype_N, (del_qual_C), { NULL }, NULL, "host"
	, "Host name" }
};
static dnsextlang_stanza t0005 = {
	"CNAME", 5, (del_option_A),
	"the canonical name for an alias [RFC1035]",
	1, t0005_fields
};
static dnsextlang_field t0006_fields[7] = {
	{ del_ftype_N, (del_qual_C), { NULL }, NULL, "primary"
	, "Primary server name" },
	{ del_ftype_N, (del_qual_A), { NULL }, NULL, "mailbox"
	, "Responsible mailbox" },
	{ del_ftype_I4, 0, { NULL }, NULL, "serial"
	, "Serial number" },
	{ del_ftype_I4, 0, { NULL }, NULL, "refresh"
	, "Refresh time (seconds)" },
	{ del_ftype_I4, 0, { NULL }, NULL, "retry"
	, "Retry time (seconds)" },
	{ del_ftype_I4, 0, { NULL }, NULL, "expire"
	, "Expire time (seconds)" },
	{ del_ftype_I4, 0, { NULL }, NULL, "minimum"
	, "Minium time (seconds)" }
};
static dnsextlang_stanza t0006 = {
	"SOA", 6, (del_option_A),
	"marks the start of a zone of authority [RFC1035]",
	7, t0006_fields
};
static dnsextlang_field t0007_fields[1] = {
	{ del_ftype_N, (del_qual_C), { NULL }, NULL, "host"
	, "Host name" }
};
static dnsextlang_stanza t0007 = {
	"MB", 7, (del_option_A|del_option_E),
	"a mailbox domain name (EXPERIMENTAL) [RFC1035]",
	1, t0007_fields
};
static dnsextlang_field t0008_fields[1] = {
	{ del_ftype_N, (del_qual_A), { NULL }, NULL, "mailbox"
	, "Mailbox name" }
};
static dnsextlang_stanza t0008 = {
	"MG", 8, (del_option_A|del_option_E),
	"a mail group member (EXPERIMENTAL) [RFC1035]",
	1, t0008_fields
};
static dnsextlang_field t0009_fields[1] = {
	{ del_ftype_N, (del_qual_A), { NULL }, NULL, "mailbox"
	, "Mailbox name" }
};
static dnsextlang_stanza t0009 = {
	"MR", 9, (del_option_A|del_option_E),
	"a mail rename domain name (EXPERIMENTAL) [RFC1035]",
	1, t0009_fields
};
static dnsextlang_field t000b_fields[3] = {
	{ del_ftype_A, 0, { NULL }, NULL, NULL
	, "IPv4 address" },
	{ del_ftype_I1, 0, { NULL }, NULL, NULL
	, "Protocol number" },
	{ del_ftype_Z, (del_qual_WKS), { NULL }, NULL, "bitmap"
	, "Bit Map" }
};
static dnsextlang_stanza t000b = {
	"WKS", 11, (del_option_I),
	"a well known service description [RFC1035]",
	3, t000b_fields
};
static dnsextlang_field t000c_fields[1] = {
	{ del_ftype_N, (del_qual_C), { NULL }, NULL, "host"
	, "Host name" }
};
static dnsextlang_stanza t000c = {
	"PTR", 12, (del_option_A),
	"a domain name pointer [RFC1035]",
	1, t000c_fields
};
static dnsextlang_field t000d_fields[2] = {
	{ del_ftype_S, 0, { NULL }, NULL, "cpu"
	, "CPU type" },
	{ del_ftype_S, 0, { NULL }, NULL, "os"
	, "Operating system" }
};
static dnsextlang_stanza t000d = {
	"HINFO", 13, (del_option_A),
	"host information [RFC1035]",
	2, t000d_fields
};
static dnsextlang_field t000e_fields[2] = {
	{ del_ftype_N, (del_qual_A), { NULL }, NULL, "respbox"
	, "Responsible mailbox" },
	{ del_ftype_N, (del_qual_A), { NULL }, NULL, "errbox"
	, "Error mailbox" }
};
static dnsextlang_stanza t000e = {
	"MINFO", 14, (del_option_A),
	"mailbox or mail list information [RFC1035]",
	2, t000e_fields
};
static dnsextlang_field t000f_fields[2] = {
	{ del_ftype_I2, 0, { NULL }, NULL, "priority"
	, "Priority (lower values are higher priority)" },
	{ del_ftype_N, (del_qual_C), { NULL }, NULL, "hostname"
	, "Host name" }
};
static dnsextlang_stanza t000f = {
	"MX", 15, (del_option_A),
	"mail exchange [RFC1035]",
	2, t000f_fields
};
static dnsextlang_field t0010_fields[1] = {
	{ del_ftype_S, (del_qual_M), { NULL }, NULL, "text"
	, "Strings" }
};
static dnsextlang_stanza t0010 = {
	"TXT", 16, (del_option_A),
	"text strings [RFC1035]",
	1, t0010_fields
};
static dnsextlang_field t0011_fields[2] = {
	{ del_ftype_N, (del_qual_A), { NULL }, NULL, "mailbox"
	, "Mailbox" },
	{ del_ftype_N, 0, { NULL }, NULL, "text"
	, "Text location" }
};
static dnsextlang_stanza t0011 = {
	"RP", 17, (del_option_A),
	"for Responsible Person [RFC1183]",
	2, t0011_fields
};
static dnsextlang_field t0012_fields[2] = {
	{ del_ftype_I2, 0, { NULL }, NULL, "subtype"
	, "Subtype" },
	{ del_ftype_N, 0, { NULL }, NULL, "hostname"
	, "Hostname" }
};
static dnsextlang_stanza t0012 = {
	"AFSDB", 18, (del_option_A),
	"for AFS Data Base location [RFC1183][RFC5864]",
	2, t0012_fields
};
static dnsextlang_field t0013_fields[1] = {
	{ del_ftype_S, 0, { NULL }, NULL, "address"
	, "PSDN address" }
};
static dnsextlang_stanza t0013 = {
	"X25", 19, (del_option_A),
	"for X.25 PSDN address [RFC1183]",
	1, t0013_fields
};
static dnsextlang_field t0014_fields[1] = {
	{ del_ftype_S, (del_qual_M), { NULL }, NULL, "address"
	, "ISDN address, and optional subaddress" }
};
static dnsextlang_stanza t0014 = {
	"ISDN", 20, (del_option_A),
	"for ISDN address [RFC1183]",
	1, t0014_fields
};
static dnsextlang_field t0015_fields[2] = {
	{ del_ftype_I2, 0, { NULL }, NULL, "preference"
	, "Preference" },
	{ del_ftype_N, 0, { NULL }, NULL, "hostname"
	, "Intermediate host" }
};
static dnsextlang_stanza t0015 = {
	"RT", 21, (del_option_A),
	"for Route Through [RFC1183]",
	2, t0015_fields
};
static dnsextlang_field t0016_fields[1] = {
	{ del_ftype_Z, (del_qual_NSAP), { NULL }, NULL, "address"
	, "NSAP Address" }
};
static dnsextlang_stanza t0016 = {
	"NSAP", 22, (del_option_I),
	"for NSAP address, NSAP style A record [RFC1706]",
	1, t0016_fields
};
static dnsextlang_field t0017_fields[1] = {
	{ del_ftype_N, 0, { NULL }, NULL, "hostname"
	, "Host name" }
};
static dnsextlang_stanza t0017 = {
	"NSAP-PTR", 23, (del_option_I),
	"for domain name pointer, NSAP style [RFC1348][RFC1637]",
	1, t0017_fields
};
static dnsextlang_field t0018_fields[9] = {
	{ del_ftype_I2, 0, { NULL }, NULL, "sigtype"
	, "Type covered" },
	{ del_ftype_I1, 0, { NULL }, NULL, "algorithm"
	, "Algorithm" },
	{ del_ftype_I1, 0, { NULL }, NULL, "labels"
	, "Labels" },
	{ del_ftype_I4, 0, { NULL }, NULL, "ttl"
	, "Original TTL" },
	{ del_ftype_T, 0, { NULL }, NULL, "expires"
	, "Signature expiration time" },
	{ del_ftype_T, 0, { NULL }, NULL, "signed"
	, "Time signed" },
	{ del_ftype_I2, 0, { NULL }, NULL, "footprint"
	, "Key footprint" },
	{ del_ftype_N, (del_qual_C), { NULL }, NULL, "name"
	, "Signer's name" },
	{ del_ftype_B64, 0, { NULL }, NULL, "signature"
	, "Signature data" }
};
static dnsextlang_stanza t0018 = {
	"SIG", 24, (del_option_A),
	"for security signature [RFC4034]",
	9, t0018_fields
};
static dnsextlang_field t0019_fields[4] = {
	{ del_ftype_I2, 0, { NULL }, NULL, "flags"
	, "Flags" },
	{ del_ftype_I1, 0, { NULL }, NULL, "protocol"
	, "Protocol" },
	{ del_ftype_I1, 0, { NULL }, NULL, "algorithm"
	, "Algorithm" },
	{ del_ftype_B64, 0, { NULL }, NULL, "data"
	, "Key data" }
};
static dnsextlang_stanza t0019 = {
	"KEY", 25, (del_option_A),
	"for security key [RFC4034]",
	4, t0019_fields
};
static dnsextlang_field t001a_fields[3] = {
	{ del_ftype_I2, 0, { NULL }, NULL, "pref"
	, "Preference" },
	{ del_ftype_N, 0, { NULL }, NULL, "idomain"
	, "Internet mail domain" },
	{ del_ftype_N, 0, { NULL }, NULL, "xdomain"
	, "X.400 mail domain" }
};
static dnsextlang_stanza t001a = {
	"PX", 26, (del_option_I),
	"X.400 mail mapping information [RFC2163]",
	3, t001a_fields
};
static dnsextlang_field t001b_fields[3] = {
	{ del_ftype_S, 0, { NULL }, NULL, "longitude"
	, "Longitude (decimal degrees)" },
	{ del_ftype_S, 0, { NULL }, NULL, "latitude"
	, "Latitude (decimal degrees)" },
	{ del_ftype_S, 0, { NULL }, NULL, "altitude"
	, "Altitude (meters)" }
};
static dnsextlang_stanza t001b = {
	"GPOS", 27, (del_option_A),
	"Geographical Position [RFC1712]",
	3, t001b_fields
};
static dnsextlang_field t001c_fields[1] = {
	{ del_ftype_AAAA, 0, { NULL }, NULL, "address"
	, "Address" }
};
static dnsextlang_stanza t001c = {
	"AAAA", 28, (del_option_I),
	"IP6 Address [RFC3596]",
	1, t001c_fields
};
static dnsextlang_field t001d_fields[7] = {
	{ del_ftype_I1, 0, { NULL }, NULL, "version"
	, "Version" },
	{ del_ftype_I1, 0, { NULL }, NULL, "sphere"
	, "Sphere size" },
	{ del_ftype_I2, 0, { NULL }, NULL, "hprecision"
	, "Horiz precision" },
	{ del_ftype_I2, 0, { NULL }, NULL, "vprecision"
	, "Vert precision" },
	{ del_ftype_I4, 0, { NULL }, NULL, "latitude"
	, "Latitude (offset milliseconds)" },
	{ del_ftype_I4, 0, { NULL }, NULL, "longitude"
	, "Longitude (offset milliseconds)" },
	{ del_ftype_I4, 0, { NULL }, NULL, "altitude"
	, "Altitude (offset cm)" }
};
static dnsextlang_stanza t001d = {
	"LOC", 29, (del_option_A),
	"Location Information [RFC1876]",
	7, t001d_fields
};
static dnsextlang_field t001e_fields[2] = {
	{ del_ftype_N, (del_qual_C), { NULL }, NULL, "next"
	, "Domain" },
	{ del_ftype_Z, (del_qual_NXT), { NULL }, NULL, "rrtypes"
	, "Bitmap of rrtypes" }
};
static dnsextlang_stanza t001e = {
	"NXT", 30, (del_option_A|del_option_O),
	"Next Domain (OBSOLETE) [RFC3755][RFC2535]",
	2, t001e_fields
};
static dnsextlang_field t0021_fields[4] = {
	{ del_ftype_I2, 0, { NULL }, NULL, "priority"
	, "Priority" },
	{ del_ftype_I2, 0, { NULL }, NULL, "weight"
	, "Weight" },
	{ del_ftype_I2, 0, { NULL }, NULL, "port"
	, "Port" },
	{ del_ftype_N, 0, { NULL }, NULL, "target"
	, "Target host name" }
};
static dnsextlang_stanza t0021 = {
	"SRV", 33, (del_option_I),
	"Server Selection [1][RFC2782]",
	4, t0021_fields
};
static dnsextlang_field t0023_fields[6] = {
	{ del_ftype_I2, 0, { NULL }, NULL, "order"
	, "Order" },
	{ del_ftype_I2, 0, { NULL }, NULL, "pref"
	, "Preference" },
	{ del_ftype_S, 0, { NULL }, NULL, "flags"
	, "Flags" },
	{ del_ftype_S, 0, { NULL }, NULL, "services"
	, "Services" },
	{ del_ftype_S, 0, { NULL }, NULL, "regex"
	, "Regular expression" },
	{ del_ftype_N, 0, { NULL }, NULL, "replacement"
	, "Replacement" }
};
static dnsextlang_stanza t0023 = {
	"NAPTR", 35, (del_option_I),
	"Naming Authority Pointer [RFC2915][RFC2168][RFC3403]",
	6, t0023_fields
};
static dnsextlang_field t0024_fields[2] = {
	{ del_ftype_I2, 0, { NULL }, NULL, "pref"
	, "Preference" },
	{ del_ftype_N, 0, { NULL }, NULL, "exchanger"
	, "Exchanger" }
};
static dnsextlang_stanza t0024 = {
	"KX", 36, (del_option_I),
	"Key Exchanger [RFC2230]",
	2, t0024_fields
};
static const char *t0025_0_00xx[256] = {
	  NULL, "PKIX", "SPKI", "PGP", "IPKIX", "ISPKI", "IPGP", "ACPKIX",
	 "IACPKIX", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, "URI", "OID", NULL};
static const char **t0025_0_xxxx[256] = {
	  t0025_0_00xx, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL};
static ldh_radix t0025_0_ACPKIX = { "ACPKIX", 6, 1, 7,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t0025_0_IACPKIX = { "ACPKIX", 6, 1, 8,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t0025_0_IPGP = { "GP", 2, 1, 6,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t0025_0_IPKIX = { "KIX", 3, 1, 4,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t0025_0_IP = { "P", 1, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL,&t0025_0_IPGP, NULL, NULL, NULL,
	 &t0025_0_IPKIX, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL } };
static ldh_radix t0025_0_ISPKI = { "SPKI", 4, 1, 5,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t0025_0_I = { "I", 1, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &t0025_0_IACPKIX, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL,&t0025_0_IP, NULL, NULL,
	 &t0025_0_ISPKI, NULL, NULL, NULL, NULL, NULL, NULL, NULL } };
static ldh_radix t0025_0_OID = { "OID", 3, 1, 254,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t0025_0_PGP = { "GP", 2, 1, 3,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t0025_0_PKIX = { "KIX", 3, 1, 1,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t0025_0_P = { "P", 1, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL,&t0025_0_PGP, NULL, NULL, NULL,
	 &t0025_0_PKIX, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL } };
static ldh_radix t0025_0_SPKI = { "SPKI", 4, 1, 2,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t0025_0_URI = { "URI", 3, 1, 253,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t0025_0_ldh_radix = { "", 0, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &t0025_0_ACPKIX, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &t0025_0_I, NULL, NULL, NULL, NULL, NULL,&t0025_0_OID,&t0025_0_P,
	  NULL, NULL,&t0025_0_SPKI, NULL,&t0025_0_URI, NULL, NULL, NULL,
	  NULL, NULL } };
static const char *t0025_2_xx[256] = {
	  NULL, "RSAMD5", "DH", "DSA", "ECC", "RSASHA1", NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, "INDIRECT", "PRIVATEDNS", "PRIVATEOID", NULL};
static ldh_radix t0025_2_DH = { "H", 1, 1, 2,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t0025_2_DSA = { "SA", 2, 1, 3,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t0025_2_D = { "D", 1, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL,&t0025_2_DH, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL,&t0025_2_DSA, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL } };
static ldh_radix t0025_2_ECC = { "ECC", 3, 1, 4,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t0025_2_INDIRECT = { "INDIRECT", 8, 1, 252,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t0025_2_PRIVATEDNS = { "DNS", 3, 1, 253,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t0025_2_PRIVATEOID = { "OID", 3, 1, 254,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t0025_2_PRIVATE = { "PRIVATE", 7, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL,&t0025_2_PRIVATEDNS, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL,&t0025_2_PRIVATEOID, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL } };
static ldh_radix t0025_2_RSAMD5 = { "MD5", 3, 1, 1,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t0025_2_RSASHA1 = { "SHA1", 4, 1, 5,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t0025_2_RSA = { "RSA", 3, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &t0025_2_RSAMD5, NULL, NULL, NULL, NULL, NULL,&t0025_2_RSASHA1,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL } };
static ldh_radix t0025_2_ldh_radix = { "", 0, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL,&t0025_2_D,&t0025_2_ECC, NULL, NULL, NULL,&t0025_2_INDIRECT,
	  NULL, NULL, NULL, NULL, NULL, NULL,&t0025_2_PRIVATE, NULL,
	 &t0025_2_RSA, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL } };
static dnsextlang_field t0025_fields[4] = {
	{ del_ftype_I2, 0
	, { (void *)t0025_0_xxxx }, &t0025_0_ldh_radix, "type"
	, "Type" },
	{ del_ftype_I2, 0, { NULL }, NULL, "tag"
	, "Key tag" },
	{ del_ftype_I1, 0
	, { (void *)t0025_2_xx }, &t0025_2_ldh_radix, "algorithm"
	, "Algorithm" },
	{ del_ftype_B64, 0, { NULL }, NULL, "certificate"
	, "Certificate or CRL" }
};
static dnsextlang_stanza t0025 = {
	"CERT", 37, (del_option_A),
	"CERT [RFC4398]",
	4, t0025_fields
};
static dnsextlang_field t0026_fields[3] = {
	{ del_ftype_Z, (del_qual_A6P), { NULL }, NULL, "preflen"
	, "Prefix length" },
	{ del_ftype_Z, (del_qual_A6S), { NULL }, NULL, "suffix"
	, "Address suffix" },
	{ del_ftype_N, 0, { NULL }, NULL, "prefname"
	, "Prefix name" }
};
static dnsextlang_stanza t0026 = {
	"A6", 38, (del_option_I|del_option_O),
	"A6 (OBSOLETE - use AAAA) [RFC3226][RFC2874][RFC6563]",
	3, t0026_fields
};
static dnsextlang_field t0027_fields[1] = {
	{ del_ftype_N, 0, { NULL }, NULL, "source"
	, "Source name" }
};
static dnsextlang_stanza t0027 = {
	"DNAME", 39, (del_option_A),
	"DNAME [RFC6672]",
	1, t0027_fields
};
static dnsextlang_field t002a_fields[1] = {
	{ del_ftype_Z, (del_qual_APL), { NULL }, NULL, "prefixes"
	, "Prefixes" }
};
static dnsextlang_stanza t002a = {
	"APL", 42, (del_option_I),
	"APL [RFC3123]",
	1, t002a_fields
};
static const char *t002b_1_xx[256] = {
	  NULL, "RSAMD5", "DH", "DSA", "ECC", "RSASHA1", "DSA-NSEC-SHA1",
	 "RSASHA1-NSEC3-SHA1", "RSASHA256", NULL, "RSASHA512", NULL,
	 "ECC-GOST", "ECDSAP256SHA256", "ECDSAP384SHA384", NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, "INDIRECT", "PRIVATEDNS", "PRIVATEOID", NULL};
static ldh_radix t002b_1_DH = { "H", 1, 1, 2,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t002b_1_DSA_NSEC_SHA1 = { "-NSEC-SHA1", 10, 1, 6,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t002b_1_DSA = { "SA", 2, 1, 3,
	{&t002b_1_DSA_NSEC_SHA1, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL } };
static ldh_radix t002b_1_D = { "D", 1, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL,&t002b_1_DH, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL,&t002b_1_DSA, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL } };
static ldh_radix t002b_1_ECC_GOST = { "-GOST", 5, 1, 12,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t002b_1_ECC = { "C", 1, 1, 4,
	{&t002b_1_ECC_GOST, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL } };
static ldh_radix t002b_1_ECDSAP256SHA256 = { "256SHA256", 9, 1, 13,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t002b_1_ECDSAP384SHA384 = { "384SHA384", 9, 1, 14,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t002b_1_ECDSAP = { "DSAP", 4, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL,&t002b_1_ECDSAP256SHA256,
	 &t002b_1_ECDSAP384SHA384, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL } };
static ldh_radix t002b_1_EC = { "EC", 2, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &t002b_1_ECC,&t002b_1_ECDSAP, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL } };
static ldh_radix t002b_1_INDIRECT = { "INDIRECT", 8, 1, 252,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t002b_1_PRIVATEDNS = { "DNS", 3, 1, 253,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t002b_1_PRIVATEOID = { "OID", 3, 1, 254,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t002b_1_PRIVATE = { "PRIVATE", 7, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL,&t002b_1_PRIVATEDNS, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL,&t002b_1_PRIVATEOID, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL } };
static ldh_radix t002b_1_RSAMD5 = { "MD5", 3, 1, 1,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t002b_1_RSASHA1_NSEC3_SHA1 = { "-NSEC3-SHA1", 11, 1, 7,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t002b_1_RSASHA1 = { "1", 1, 1, 5,
	{&t002b_1_RSASHA1_NSEC3_SHA1, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL } };
static ldh_radix t002b_1_RSASHA256 = { "256", 3, 1, 8,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t002b_1_RSASHA512 = { "512", 3, 1, 10,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t002b_1_RSASHA = { "SHA", 3, 0, 0,
	{ NULL, NULL, NULL, NULL,&t002b_1_RSASHA1,&t002b_1_RSASHA256, NULL,
	  NULL,&t002b_1_RSASHA512, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL } };
static ldh_radix t002b_1_RSA = { "RSA", 3, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &t002b_1_RSAMD5, NULL, NULL, NULL, NULL, NULL,&t002b_1_RSASHA,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL } };
static ldh_radix t002b_1_ldh_radix = { "", 0, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL,&t002b_1_D,&t002b_1_EC, NULL, NULL, NULL,&t002b_1_INDIRECT,
	  NULL, NULL, NULL, NULL, NULL, NULL,&t002b_1_PRIVATE, NULL,
	 &t002b_1_RSA, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL } };
static const char *t002b_2_xx[256] = {
	  NULL, "SHA-1", "SHA-256", "GOST", "SHA-384", NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL};
static ldh_radix t002b_2_GOST = { "GOST", 4, 1, 3,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t002b_2_SHA_1 = { "1", 1, 1, 1,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t002b_2_SHA_256 = { "256", 3, 1, 2,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t002b_2_SHA_384 = { "384", 3, 1, 4,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t002b_2_SHA_ = { "SHA-", 4, 0, 0,
	{ NULL, NULL, NULL, NULL,&t002b_2_SHA_1,&t002b_2_SHA_256,
	 &t002b_2_SHA_384, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL } };
static ldh_radix t002b_2_ldh_radix = { "", 0, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL,&t002b_2_GOST, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL,&t002b_2_SHA_, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL } };
static dnsextlang_field t002b_fields[4] = {
	{ del_ftype_I2, 0, { NULL }, NULL, "keytag"
	, "Key tag" },
	{ del_ftype_I1, 0
	, { (void *)t002b_1_xx }, &t002b_1_ldh_radix, "algorithm"
	, "Algorithm" },
	{ del_ftype_I1, 0
	, { (void *)t002b_2_xx }, &t002b_2_ldh_radix, "digtype"
	, "Digest type" },
	{ del_ftype_X, 0, { NULL }, NULL, "digest"
	, "Digest" }
};
static dnsextlang_stanza t002b = {
	"DS", 43, (del_option_A),
	"Delegation Signer [RFC4034][RFC3658]",
	4, t002b_fields
};
static dnsextlang_field t002c_fields[3] = {
	{ del_ftype_I1, 0, { NULL }, NULL, "algorithm"
	, "Algorithm" },
	{ del_ftype_I1, 0, { NULL }, NULL, "ftype"
	, "Fingerprint type" },
	{ del_ftype_X, 0, { NULL }, NULL, "fingerprint"
	, "Fingerprint" }
};
static dnsextlang_stanza t002c = {
	"SSHFP", 44, (del_option_A),
	"SSH Key Fingerprint [RFC4255]",
	3, t002c_fields
};
static dnsextlang_field t002d_fields[5] = {
	{ del_ftype_I1, 0, { NULL }, NULL, "prec"
	, "Precedence" },
	{ del_ftype_I1, 0, { NULL }, NULL, "gtype"
	, "Gateway type" },
	{ del_ftype_I1, 0, { NULL }, NULL, "algorithm"
	, "Algorithm" },
	{ del_ftype_Z, (del_qual_IPSECKEY), { NULL }, NULL, "gateway"
	, "Gateway" },
	{ del_ftype_B64, 0, { NULL }, NULL, "key"
	, "Public key" }
};
static dnsextlang_stanza t002d = {
	"IPSECKEY", 45, (del_option_I),
	"IPSECKEY [RFC4025]",
	5, t002d_fields
};
static const char *t002e_1_xx[256] = {
	  NULL, "RSAMD5", "DH", "DSA", "ECC", "RSASHA1", NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, "INDIRECT", "PRIVATEDNS", "PRIVATEOID", NULL};
static ldh_radix t002e_1_DH = { "H", 1, 1, 2,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t002e_1_DSA = { "SA", 2, 1, 3,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t002e_1_D = { "D", 1, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL,&t002e_1_DH, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL,&t002e_1_DSA, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL } };
static ldh_radix t002e_1_ECC = { "ECC", 3, 1, 4,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t002e_1_INDIRECT = { "INDIRECT", 8, 1, 252,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t002e_1_PRIVATEDNS = { "DNS", 3, 1, 253,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t002e_1_PRIVATEOID = { "OID", 3, 1, 254,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t002e_1_PRIVATE = { "PRIVATE", 7, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL,&t002e_1_PRIVATEDNS, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL,&t002e_1_PRIVATEOID, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL } };
static ldh_radix t002e_1_RSAMD5 = { "MD5", 3, 1, 1,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t002e_1_RSASHA1 = { "SHA1", 4, 1, 5,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t002e_1_RSA = { "RSA", 3, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &t002e_1_RSAMD5, NULL, NULL, NULL, NULL, NULL,&t002e_1_RSASHA1,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL } };
static ldh_radix t002e_1_ldh_radix = { "", 0, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL,&t002e_1_D,&t002e_1_ECC, NULL, NULL, NULL,&t002e_1_INDIRECT,
	  NULL, NULL, NULL, NULL, NULL, NULL,&t002e_1_PRIVATE, NULL,
	 &t002e_1_RSA, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL } };
static dnsextlang_field t002e_fields[9] = {
	{ del_ftype_R, 0, { NULL }, NULL, "rrtype"
	, "Type covered (Type mnemonic)" },
	{ del_ftype_I1, 0
	, { (void *)t002e_1_xx }, &t002e_1_ldh_radix, "algorithm"
	, "Algorithm" },
	{ del_ftype_I1, 0, { NULL }, NULL, "labels"
	, "Labels" },
	{ del_ftype_I4, 0, { NULL }, NULL, "origttl"
	, "Original TTL" },
	{ del_ftype_T, 0, { NULL }, NULL, "expire"
	, "Signature expiration (timestamp)" },
	{ del_ftype_T, 0, { NULL }, NULL, "inception"
	, "Signature inception (timestamp)" },
	{ del_ftype_I2, 0, { NULL }, NULL, "keytag"
	, "Key tag" },
	{ del_ftype_N, 0, { NULL }, NULL, "signer"
	, "Signer's name" },
	{ del_ftype_B64, 0, { NULL }, NULL, "signature"
	, "Signature" }
};
static dnsextlang_stanza t002e = {
	"RRSIG", 46, (del_option_A),
	"RRSIG [RFC4034][RFC3755]",
	9, t002e_fields
};
static dnsextlang_field t002f_fields[2] = {
	{ del_ftype_N, 0, { NULL }, NULL, "next"
	, "Next domain name" },
	{ del_ftype_R, (del_qual_L), { NULL }, NULL, "types"
	, "Type bitmaps (as window blocks)" }
};
static dnsextlang_stanza t002f = {
	"NSEC", 47, (del_option_A),
	"NSEC [RFC4034][RFC3755]",
	2, t002f_fields
};
static const char *t0030_2_xx[256] = {
	  NULL, "RSAMD5", "DH", "DSA", "ECC", "RSASHA1", NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, "INDIRECT", "PRIVATEDNS", "PRIVATEOID", NULL};
static ldh_radix t0030_2_DH = { "H", 1, 1, 2,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t0030_2_DSA = { "SA", 2, 1, 3,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t0030_2_D = { "D", 1, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL,&t0030_2_DH, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL,&t0030_2_DSA, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL } };
static ldh_radix t0030_2_ECC = { "ECC", 3, 1, 4,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t0030_2_INDIRECT = { "INDIRECT", 8, 1, 252,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t0030_2_PRIVATEDNS = { "DNS", 3, 1, 253,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t0030_2_PRIVATEOID = { "OID", 3, 1, 254,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t0030_2_PRIVATE = { "PRIVATE", 7, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL,&t0030_2_PRIVATEDNS, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL,&t0030_2_PRIVATEOID, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL } };
static ldh_radix t0030_2_RSAMD5 = { "MD5", 3, 1, 1,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t0030_2_RSASHA1 = { "SHA1", 4, 1, 5,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t0030_2_RSA = { "RSA", 3, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &t0030_2_RSAMD5, NULL, NULL, NULL, NULL, NULL,&t0030_2_RSASHA1,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL } };
static ldh_radix t0030_2_ldh_radix = { "", 0, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL,&t0030_2_D,&t0030_2_ECC, NULL, NULL, NULL,&t0030_2_INDIRECT,
	  NULL, NULL, NULL, NULL, NULL, NULL,&t0030_2_PRIVATE, NULL,
	 &t0030_2_RSA, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL } };
static dnsextlang_field t0030_fields[4] = {
	{ del_ftype_I2, 0, { NULL }, NULL, "flags"
	, "Flags" },
	{ del_ftype_I1, 0, { NULL }, NULL, "protocol"
	, "Protocol (must be 3)" },
	{ del_ftype_I1, 0
	, { (void *)t0030_2_xx }, &t0030_2_ldh_radix, "algorithm"
	, "Algorithm" },
	{ del_ftype_B64, 0, { NULL }, NULL, "publickey"
	, "Public key" }
};
static dnsextlang_stanza t0030 = {
	"DNSKEY", 48, (del_option_A),
	"DNSKEY [RFC4034][RFC3755]",
	4, t0030_fields
};
static dnsextlang_field t0031_fields[1] = {
	{ del_ftype_B64, 0, { NULL }, NULL, "dhcpinfo"
	, "DHCP information" }
};
static dnsextlang_stanza t0031 = {
	"DHCID", 49, (del_option_I),
	"DHCID [RFC4701]",
	1, t0031_fields
};
static const char *t0032_0_xx[256] = {
	  NULL, "SHA-1", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL};
static ldh_radix t0032_0_SHA_1 = { "SHA-1", 5, 1, 1,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static const char *t0032_1_xx[256] = {
	  NULL, "OPTOUT", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL};
static ldh_radix t0032_1_OPTOUT = { "OPTOUT", 6, 1, 1,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static dnsextlang_field t0032_fields[6] = {
	{ del_ftype_I1, 0
	, { (void *)t0032_0_xx }, &t0032_0_SHA_1, "algorithm"
	, "Hash algorithm" },
	{ del_ftype_I1, 0
	, { (void *)t0032_1_xx }, &t0032_1_OPTOUT, "flags"
	, "Flags" },
	{ del_ftype_I2, 0, { NULL }, NULL, "iterations"
	, "Iterations" },
	{ del_ftype_X, (del_qual_C), { NULL }, NULL, "salt"
	, "Salt" },
	{ del_ftype_B32, 0, { NULL }, NULL, "next"
	, "Next hashed owner" },
	{ del_ftype_R, (del_qual_L), { NULL }, NULL, "types"
	, "Type bitmaps (as window blocks)" }
};
static dnsextlang_stanza t0032 = {
	"NSEC3", 50, (del_option_A),
	"NSEC3 [RFC5155]",
	6, t0032_fields
};
static const char *t0033_0_xx[256] = {
	  NULL, "SHA-1", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL};
static ldh_radix t0033_0_SHA_1 = { "SHA-1", 5, 1, 1,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static const char *t0033_1_xx[256] = {
	  NULL, "OPTOUT", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL};
static ldh_radix t0033_1_OPTOUT = { "OPTOUT", 6, 1, 1,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static dnsextlang_field t0033_fields[4] = {
	{ del_ftype_I1, 0
	, { (void *)t0033_0_xx }, &t0033_0_SHA_1, "algorithm"
	, "Hash algorithm" },
	{ del_ftype_I1, 0
	, { (void *)t0033_1_xx }, &t0033_1_OPTOUT, "flags"
	, "Flags" },
	{ del_ftype_I2, 0, { NULL }, NULL, "iterations"
	, "Iterations" },
	{ del_ftype_X, (del_qual_C), { NULL }, NULL, "salt"
	, "Salt" }
};
static dnsextlang_stanza t0033 = {
	"NSEC3PARAM", 51, (del_option_A),
	"NSEC3PARAM [RFC5155]",
	4, t0033_fields
};
static dnsextlang_field t0034_fields[4] = {
	{ del_ftype_I1, 0, { NULL }, NULL, "usage"
	, "Certificate usage" },
	{ del_ftype_I1, 0, { NULL }, NULL, "selector"
	, "Certificate selector" },
	{ del_ftype_I1, 0, { NULL }, NULL, "mtype"
	, "Matching Type" },
	{ del_ftype_X, 0, { NULL }, NULL, "cert"
	, "Certificate association data" }
};
static dnsextlang_stanza t0034 = {
	"TLSA", 52, (del_option_A),
	"TLSA [RFC6698]",
	4, t0034_fields
};
static dnsextlang_field t0035_fields[4] = {
	{ del_ftype_I1, 0, { NULL }, NULL, "usage"
	, "Certificate usage" },
	{ del_ftype_I1, 0, { NULL }, NULL, "selector"
	, "Certificate selector" },
	{ del_ftype_I1, 0, { NULL }, NULL, "mtype"
	, "Matching Type" },
	{ del_ftype_X, 0, { NULL }, NULL, "cert"
	, "Certificate association data" }
};
static dnsextlang_stanza t0035 = {
	"SMIMEA", 53, (del_option_A),
	"S/MIME cert association [RFC8162]",
	4, t0035_fields
};
static dnsextlang_field t0037_fields[4] = {
	{ del_ftype_I1, 0, { NULL }, NULL, "pkalg"
	, "PK algorithm" },
	{ del_ftype_Z, (del_qual_HIPHIT), { NULL }, NULL, "hit"
	, "HIT" },
	{ del_ftype_Z, (del_qual_HIPPK), { NULL }, NULL, "pubkey"
	, "Public Key" },
	{ del_ftype_N, (del_qual_O|del_qual_M), { NULL }, NULL, "servers"
	, "Rendezvous servers" }
};
static dnsextlang_stanza t0037 = {
	"HIP", 55, (del_option_A),
	"Host Identity Protocol [RFC8005]",
	4, t0037_fields
};
static const char *t003b_1_xx[256] = {
	  NULL, "RSAMD5", "DH", "DSA", "ECC", "RSASHA1", "DSA-NSEC-SHA1",
	 "RSASHA1-NSEC3-SHA1", "RSASHA256", NULL, "RSASHA512", NULL,
	 "ECC-GOST", "ECDSAP256SHA256", "ECDSAP384SHA384", NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, "INDIRECT", "PRIVATEDNS", "PRIVATEOID", NULL};
static ldh_radix t003b_1_DH = { "H", 1, 1, 2,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t003b_1_DSA_NSEC_SHA1 = { "-NSEC-SHA1", 10, 1, 6,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t003b_1_DSA = { "SA", 2, 1, 3,
	{&t003b_1_DSA_NSEC_SHA1, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL } };
static ldh_radix t003b_1_D = { "D", 1, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL,&t003b_1_DH, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL,&t003b_1_DSA, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL } };
static ldh_radix t003b_1_ECC_GOST = { "-GOST", 5, 1, 12,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t003b_1_ECC = { "C", 1, 1, 4,
	{&t003b_1_ECC_GOST, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL } };
static ldh_radix t003b_1_ECDSAP256SHA256 = { "256SHA256", 9, 1, 13,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t003b_1_ECDSAP384SHA384 = { "384SHA384", 9, 1, 14,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t003b_1_ECDSAP = { "DSAP", 4, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL,&t003b_1_ECDSAP256SHA256,
	 &t003b_1_ECDSAP384SHA384, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL } };
static ldh_radix t003b_1_EC = { "EC", 2, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &t003b_1_ECC,&t003b_1_ECDSAP, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL } };
static ldh_radix t003b_1_INDIRECT = { "INDIRECT", 8, 1, 252,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t003b_1_PRIVATEDNS = { "DNS", 3, 1, 253,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t003b_1_PRIVATEOID = { "OID", 3, 1, 254,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t003b_1_PRIVATE = { "PRIVATE", 7, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL,&t003b_1_PRIVATEDNS, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL,&t003b_1_PRIVATEOID, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL } };
static ldh_radix t003b_1_RSAMD5 = { "MD5", 3, 1, 1,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t003b_1_RSASHA1_NSEC3_SHA1 = { "-NSEC3-SHA1", 11, 1, 7,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t003b_1_RSASHA1 = { "1", 1, 1, 5,
	{&t003b_1_RSASHA1_NSEC3_SHA1, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL } };
static ldh_radix t003b_1_RSASHA256 = { "256", 3, 1, 8,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t003b_1_RSASHA512 = { "512", 3, 1, 10,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t003b_1_RSASHA = { "SHA", 3, 0, 0,
	{ NULL, NULL, NULL, NULL,&t003b_1_RSASHA1,&t003b_1_RSASHA256, NULL,
	  NULL,&t003b_1_RSASHA512, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL } };
static ldh_radix t003b_1_RSA = { "RSA", 3, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &t003b_1_RSAMD5, NULL, NULL, NULL, NULL, NULL,&t003b_1_RSASHA,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL } };
static ldh_radix t003b_1_ldh_radix = { "", 0, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL,&t003b_1_D,&t003b_1_EC, NULL, NULL, NULL,&t003b_1_INDIRECT,
	  NULL, NULL, NULL, NULL, NULL, NULL,&t003b_1_PRIVATE, NULL,
	 &t003b_1_RSA, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL } };
static const char *t003b_2_xx[256] = {
	  NULL, "SHA-1", "SHA-256", "GOST", "SHA-384", NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL};
static ldh_radix t003b_2_GOST = { "GOST", 4, 1, 3,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t003b_2_SHA_1 = { "1", 1, 1, 1,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t003b_2_SHA_256 = { "256", 3, 1, 2,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t003b_2_SHA_384 = { "384", 3, 1, 4,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t003b_2_SHA_ = { "SHA-", 4, 0, 0,
	{ NULL, NULL, NULL, NULL,&t003b_2_SHA_1,&t003b_2_SHA_256,
	 &t003b_2_SHA_384, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL } };
static ldh_radix t003b_2_ldh_radix = { "", 0, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL,&t003b_2_GOST, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL,&t003b_2_SHA_, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL } };
static dnsextlang_field t003b_fields[4] = {
	{ del_ftype_I2, 0, { NULL }, NULL, "keytag"
	, "Key tag" },
	{ del_ftype_I1, 0
	, { (void *)t003b_1_xx }, &t003b_1_ldh_radix, "algorithm"
	, "Algorithm" },
	{ del_ftype_I1, 0
	, { (void *)t003b_2_xx }, &t003b_2_ldh_radix, "digtype"
	, "Digest type" },
	{ del_ftype_X, 0, { NULL }, NULL, "digest"
	, "Digest" }
};
static dnsextlang_stanza t003b = {
	"CDS", 59, (del_option_A),
	"Child DS [RFC7344]",
	4, t003b_fields
};
static const char *t003c_2_xx[256] = {
	  NULL, "RSAMD5", "DH", "DSA", "ECC", "RSASHA1", NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, "INDIRECT", "PRIVATEDNS", "PRIVATEOID", NULL};
static ldh_radix t003c_2_DH = { "H", 1, 1, 2,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t003c_2_DSA = { "SA", 2, 1, 3,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t003c_2_D = { "D", 1, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL,&t003c_2_DH, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL,&t003c_2_DSA, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL } };
static ldh_radix t003c_2_ECC = { "ECC", 3, 1, 4,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t003c_2_INDIRECT = { "INDIRECT", 8, 1, 252,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t003c_2_PRIVATEDNS = { "DNS", 3, 1, 253,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t003c_2_PRIVATEOID = { "OID", 3, 1, 254,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t003c_2_PRIVATE = { "PRIVATE", 7, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL,&t003c_2_PRIVATEDNS, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL,&t003c_2_PRIVATEOID, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL } };
static ldh_radix t003c_2_RSAMD5 = { "MD5", 3, 1, 1,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t003c_2_RSASHA1 = { "SHA1", 4, 1, 5,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t003c_2_RSA = { "RSA", 3, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &t003c_2_RSAMD5, NULL, NULL, NULL, NULL, NULL,&t003c_2_RSASHA1,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL } };
static ldh_radix t003c_2_ldh_radix = { "", 0, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL,&t003c_2_D,&t003c_2_ECC, NULL, NULL, NULL,&t003c_2_INDIRECT,
	  NULL, NULL, NULL, NULL, NULL, NULL,&t003c_2_PRIVATE, NULL,
	 &t003c_2_RSA, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL } };
static dnsextlang_field t003c_fields[4] = {
	{ del_ftype_I2, 0, { NULL }, NULL, "flags"
	, "Flags" },
	{ del_ftype_I1, 0, { NULL }, NULL, "protocol"
	, "Protocol (must be 3)" },
	{ del_ftype_I1, 0
	, { (void *)t003c_2_xx }, &t003c_2_ldh_radix, "algorithm"
	, "Algorithm" },
	{ del_ftype_B64, 0, { NULL }, NULL, "publickey"
	, "Public key" }
};
static dnsextlang_stanza t003c = {
	"CDNSKEY", 60, (del_option_A),
	"DNSKEY(s) the Child wants reflected in DS [RFC7344]",
	4, t003c_fields
};
static dnsextlang_field t003d_fields[1] = {
	{ del_ftype_B64, 0, { NULL }, NULL, "key"
	, "PGP key" }
};
static dnsextlang_stanza t003d = {
	"OPENPGPKEY", 61, (del_option_A),
	"OpenPGP Key [RFC7929]",
	1, t003d_fields
};
static dnsextlang_field t003e_fields[3] = {
	{ del_ftype_I4, 0, { NULL }, NULL, "serial"
	, "SOA serial" },
	{ del_ftype_I2, 0, { NULL }, NULL, "flags"
	, "Flags" },
	{ del_ftype_R, (del_qual_L), { NULL }, NULL, "Types", NULL }
};
static dnsextlang_stanza t003e = {
	"CSYNC", 62, (del_option_A),
	"Child-To-Parent Synchronization [RFC7477]",
	3, t003e_fields
};
static const char *t003f_1_xx[256] = {
	  NULL, "SHA384", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL};
static ldh_radix t003f_1_SHA384 = { "SHA384", 6, 1, 1,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static dnsextlang_field t003f_fields[4] = {
	{ del_ftype_I4, 0, { NULL }, NULL, "serial"
	, "SOA serial" },
	{ del_ftype_I1, 0
	, { (void *)t003f_1_xx }, &t003f_1_SHA384, "digtype"
	, "Digest type" },
	{ del_ftype_I1, 0, { NULL }, NULL, "reserved"
	, "Reserved" },
	{ del_ftype_X, 0, { NULL }, NULL, "digest"
	, "Digest" }
};
static dnsextlang_stanza t003f = {
	"ZONEMD", 63, (del_option_A),
	"Message Digest for DNS Zones [draft-wessels-dns-zone-digest]",
	4, t003f_fields
};
static dnsextlang_field t0063_fields[1] = {
	{ del_ftype_S, (del_qual_M), { NULL }, NULL, "text"
	, "SPF data" }
};
static dnsextlang_stanza t0063 = {
	"SPF", 99, (del_option_A|del_option_O),
	"[RFC7208]",
	1, t0063_fields
};
static dnsextlang_field t0068_fields[2] = {
	{ del_ftype_I2, 0, { NULL }, NULL, "preference"
	, "Preference" },
	{ del_ftype_AA, 0, { NULL }, NULL, "nodeid"
	, "Node ID" }
};
static dnsextlang_stanza t0068 = {
	"NID", 104, (del_option_A),
	"[RFC6742]",
	2, t0068_fields
};
static dnsextlang_field t0069_fields[2] = {
	{ del_ftype_I2, 0, { NULL }, NULL, "preference"
	, "Preference" },
	{ del_ftype_A, 0, { NULL }, NULL, "locator"
	, "Locator32" }
};
static dnsextlang_stanza t0069 = {
	"L32", 105, (del_option_A),
	"[RFC6742]",
	2, t0069_fields
};
static dnsextlang_field t006a_fields[2] = {
	{ del_ftype_I2, 0, { NULL }, NULL, "preference"
	, "Preference" },
	{ del_ftype_AA, 0, { NULL }, NULL, "locator"
	, "Locator64" }
};
static dnsextlang_stanza t006a = {
	"L64", 106, (del_option_A),
	"[RFC6742]",
	2, t006a_fields
};
static dnsextlang_field t006b_fields[2] = {
	{ del_ftype_I2, 0, { NULL }, NULL, "preference"
	, "Preference" },
	{ del_ftype_N, 0, { NULL }, NULL, "pointer"
	, "Pointer" }
};
static dnsextlang_stanza t006b = {
	"LP", 107, (del_option_A),
	"[RFC6742]",
	2, t006b_fields
};
static dnsextlang_field t006c_fields[1] = {
	{ del_ftype_EUI48, 0, { NULL }, NULL, "address"
	, "Address (digit pairs separated by hyphens)" }
};
static dnsextlang_stanza t006c = {
	"EUI48", 108, (del_option_A),
	"an EUI-48 address [RFC7043]",
	1, t006c_fields
};
static dnsextlang_field t006d_fields[1] = {
	{ del_ftype_EUI64, 0, { NULL }, NULL, "address"
	, "Address (digit pairs separated by hyphens)" }
};
static dnsextlang_stanza t006d = {
	"EUI64", 109, (del_option_A),
	"an EUI-64 address [RFC7043]",
	1, t006d_fields
};
static const dnsextlang_stanza *t00xx[256] = {
	  NULL ,&t0001,&t0002,&t0003,&t0004,&t0005,&t0006,&t0007,&t0008,&t0009
	, NULL ,&t000b,&t000c,&t000d,&t000e,&t000f,&t0010,&t0011,&t0012,&t0013
	,&t0014,&t0015,&t0016,&t0017,&t0018,&t0019,&t001a,&t001b,&t001c,&t001d
	,&t001e, NULL , NULL ,&t0021, NULL ,&t0023,&t0024,&t0025,&t0026,&t0027
	, NULL , NULL ,&t002a,&t002b,&t002c,&t002d,&t002e,&t002f,&t0030,&t0031
	,&t0032,&t0033,&t0034,&t0035, NULL ,&t0037, NULL , NULL , NULL ,&t003b
	,&t003c,&t003d,&t003e,&t003f, NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL ,&t0063
	, NULL , NULL , NULL , NULL ,&t0068,&t0069,&t006a,&t006b,&t006c,&t006d
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL };
static dnsextlang_field t0100_fields[3] = {
	{ del_ftype_I2, 0, { NULL }, NULL, "priority"
	, "Priority" },
	{ del_ftype_I2, 0, { NULL }, NULL, "weight"
	, "Weight" },
	{ del_ftype_S, (del_qual_X), { NULL }, NULL, "target"
	, "Target" }
};
static dnsextlang_stanza t0100 = {
	"URI", 256, (del_option_A),
	"URI [RFC7553]",
	3, t0100_fields
};
static dnsextlang_field t0101_fields[3] = {
	{ del_ftype_I1, 0, { NULL }, NULL, "flags"
	, "Flags" },
	{ del_ftype_S, 0, { NULL }, NULL, "tag"
	, "Tag" },
	{ del_ftype_S, (del_qual_X), { NULL }, NULL, "value"
	, "Value" }
};
static dnsextlang_stanza t0101 = {
	"CAA", 257, (del_option_A),
	"Certification Authority Restriction [RFC6844]",
	3, t0101_fields
};
static const dnsextlang_stanza *t01xx[256] = {
	 &t0100,&t0101, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL };
static const char *t8001_1_xx[256] = {
	  NULL, "RSAMD5", "DH", "DSA", "ECC", "RSASHA1", NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, "INDIRECT", "PRIVATEDNS", "PRIVATEOID", NULL};
static ldh_radix t8001_1_DH = { "H", 1, 1, 2,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t8001_1_DSA = { "SA", 2, 1, 3,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t8001_1_D = { "D", 1, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL,&t8001_1_DH, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL,&t8001_1_DSA, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL } };
static ldh_radix t8001_1_ECC = { "ECC", 3, 1, 4,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t8001_1_INDIRECT = { "INDIRECT", 8, 1, 252,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t8001_1_PRIVATEDNS = { "DNS", 3, 1, 253,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t8001_1_PRIVATEOID = { "OID", 3, 1, 254,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t8001_1_PRIVATE = { "PRIVATE", 7, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL,&t8001_1_PRIVATEDNS, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL,&t8001_1_PRIVATEOID, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL } };
static ldh_radix t8001_1_RSAMD5 = { "MD5", 3, 1, 1,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t8001_1_RSASHA1 = { "SHA1", 4, 1, 5,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL } };
static ldh_radix t8001_1_RSA = { "RSA", 3, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &t8001_1_RSAMD5, NULL, NULL, NULL, NULL, NULL,&t8001_1_RSASHA1,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL } };
static ldh_radix t8001_1_ldh_radix = { "", 0, 0, 0,
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL,&t8001_1_D,&t8001_1_ECC, NULL, NULL, NULL,&t8001_1_INDIRECT,
	  NULL, NULL, NULL, NULL, NULL, NULL,&t8001_1_PRIVATE, NULL,
	 &t8001_1_RSA, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL } };
static dnsextlang_field t8001_fields[4] = {
	{ del_ftype_I2, 0, { NULL }, NULL, "key"
	, "Key tag" },
	{ del_ftype_I1, 0
	, { (void *)t8001_1_xx }, &t8001_1_ldh_radix, "algorithm"
	, "Algorithm" },
	{ del_ftype_I1, 0, { NULL }, NULL, "type"
	, "Digest type" },
	{ del_ftype_X, 0, { NULL }, NULL, "digest"
	, "Digest" }
};
static dnsextlang_stanza t8001 = {
	"DLV", 32769, (del_option_A),
	"DNSSEC Lookaside Validation [RFC4431]",
	4, t8001_fields
};
static const dnsextlang_stanza *t80xx[256] = {
	  NULL ,&t8001, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL };
static const dnsextlang_stanza **rrtypes_table[256] = {
	  t00xx, t01xx, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , t80xx, NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL 
	, NULL , NULL , NULL , NULL , NULL , NULL };
static ldh_trie rr_A6 = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0026 };
static ldh_trie rr_AAAA = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t001c };
static ldh_trie rr_AAA = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_AAAA,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_AA = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_AAA, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_AFSDB = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0012 };
static ldh_trie rr_AFSD = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &rr_AFSDB, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL }, NULL };
static ldh_trie rr_AFS = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL,&rr_AFSD, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_AF = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL,&rr_AFS, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_APL = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t002a };
static ldh_trie rr_AP = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_APL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_A = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_A6, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_AA, NULL,
	  NULL, NULL, NULL,&rr_AF, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL,&rr_AP, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0001 };
static ldh_trie rr_CAA = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0101 };
static ldh_trie rr_CA = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_CAA, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_CDNSKEY = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t003c };
static ldh_trie rr_CDNSKE = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &rr_CDNSKEY, NULL }, NULL };
static ldh_trie rr_CDNSK = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL,&rr_CDNSKE, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_CDNS = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_CDNSK, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_CDN = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL,&rr_CDNS, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_CDS = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t003b };
static ldh_trie rr_CD = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &rr_CDN, NULL, NULL, NULL, NULL,&rr_CDS, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_CERT = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0025 };
static ldh_trie rr_CER = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL,&rr_CERT, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_CE = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL,&rr_CER, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_CNAME = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0005 };
static ldh_trie rr_CNAM = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL,&rr_CNAME, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_CNA = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_CNAM,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_CN = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_CNA, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_CSYNC = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t003e };
static ldh_trie rr_CSYN = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &rr_CSYNC, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_CSY = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &rr_CSYN, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_CS = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &rr_CSY, NULL }, NULL };
static ldh_trie rr_C = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_CA, NULL,
	  NULL,&rr_CD,&rr_CE, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &rr_CN, NULL, NULL, NULL, NULL,&rr_CS, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_DHCID = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0031 };
static ldh_trie rr_DHCI = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL,&rr_DHCID, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_DHC = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL,&rr_DHCI, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_DH = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &rr_DHC, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_DLV = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t8001 };
static ldh_trie rr_DL = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_DLV, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_DNAME = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0027 };
static ldh_trie rr_DNAM = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL,&rr_DNAME, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_DNA = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_DNAM,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_DNSKEY = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0030 };
static ldh_trie rr_DNSKE = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &rr_DNSKEY, NULL }, NULL };
static ldh_trie rr_DNSK = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL,&rr_DNSKE, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_DNS = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_DNSK, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_DN = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_DNA, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL,&rr_DNS, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_DS = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t002b };
static ldh_trie rr_D = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL,&rr_DH, NULL, NULL, NULL,&rr_DL, NULL,
	 &rr_DN, NULL, NULL, NULL, NULL,&rr_DS, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_EUI48 = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t006c };
static ldh_trie rr_EUI4 = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &rr_EUI48, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_EUI64 = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t006d };
static ldh_trie rr_EUI6 = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_EUI64, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_EUI = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_EUI4, NULL,&rr_EUI6,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_EU = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL,&rr_EUI, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_E = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_EU, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_GPOS = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t001b };
static ldh_trie rr_GPO = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL,&rr_GPOS, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_GP = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL,&rr_GPO, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_G = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL,&rr_GP, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_HINFO = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t000d };
static ldh_trie rr_HINF = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL,&rr_HINFO, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_HIN = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL,&rr_HINF, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_HIP = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0037 };
static ldh_trie rr_HI = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &rr_HIN, NULL,&rr_HIP, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_H = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL,&rr_HI, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_IPSECKEY = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t002d };
static ldh_trie rr_IPSECKE = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &rr_IPSECKEY, NULL }, NULL };
static ldh_trie rr_IPSECK = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL,&rr_IPSECKE, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_IPSEC = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_IPSECK, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_IPSE = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &rr_IPSEC, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_IPS = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL,&rr_IPSE, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_IP = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL,&rr_IPS, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_ISDN = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0014 };
static ldh_trie rr_ISD = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &rr_ISDN, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_IS = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL,&rr_ISD, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_I = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL,&rr_IP, NULL, NULL,&rr_IS, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_KEY = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0019 };
static ldh_trie rr_KE = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &rr_KEY, NULL }, NULL };
static ldh_trie rr_KX = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0024 };
static ldh_trie rr_K = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL,&rr_KE, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_KX,
	  NULL, NULL }, NULL };
static ldh_trie rr_L32 = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0069 };
static ldh_trie rr_L3 = {
	{ NULL, NULL, NULL, NULL, NULL,&rr_L32, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_L64 = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t006a };
static ldh_trie rr_L6 = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_L64, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_LOC = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t001d };
static ldh_trie rr_LO = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &rr_LOC, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_LP = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t006b };
static ldh_trie rr_L = {
	{ NULL, NULL, NULL, NULL, NULL, NULL,&rr_L3, NULL, NULL,&rr_L6, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL,&rr_LO,&rr_LP, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_MB = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0007 };
static ldh_trie rr_MD = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0003 };
static ldh_trie rr_MF = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0004 };
static ldh_trie rr_MG = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0008 };
static ldh_trie rr_MINFO = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t000e };
static ldh_trie rr_MINF = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL,&rr_MINFO, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_MIN = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL,&rr_MINF, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_MI = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &rr_MIN, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_MR = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0009 };
static ldh_trie rr_MX = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t000f };
static ldh_trie rr_M = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_MB,
	  NULL,&rr_MD, NULL,&rr_MF,&rr_MG, NULL,&rr_MI, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL,&rr_MR, NULL, NULL, NULL, NULL, NULL,&rr_MX,
	  NULL, NULL }, NULL };
static ldh_trie rr_NAPTR = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0023 };
static ldh_trie rr_NAPT = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL,&rr_NAPTR, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_NAP = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL,&rr_NAPT, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_NA = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL,&rr_NAP, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_NID = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0068 };
static ldh_trie rr_NI = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL,&rr_NID, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_NSAP_PTR = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0017 };
static ldh_trie rr_NSAP_PT = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL,&rr_NSAP_PTR, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_NSAP_P = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL,&rr_NSAP_PT, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_NSAP_ = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL,&rr_NSAP_P, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_NSAP = {
	{&rr_NSAP_, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, &t0016 };
static ldh_trie rr_NSA = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL,&rr_NSAP, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_NSEC3PARAM = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0033 };
static ldh_trie rr_NSEC3PARA = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &rr_NSEC3PARAM, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL }, NULL };
static ldh_trie rr_NSEC3PAR = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_NSEC3PARA,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_NSEC3PA = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL,&rr_NSEC3PAR, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_NSEC3P = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_NSEC3PA,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_NSEC3 = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL,&rr_NSEC3P, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, &t0032 };
static ldh_trie rr_NSEC = {
	{ NULL, NULL, NULL, NULL, NULL, NULL,&rr_NSEC3, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, &t002f };
static ldh_trie rr_NSE = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &rr_NSEC, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_NS = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_NSA, NULL,
	  NULL, NULL,&rr_NSE, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0002 };
static ldh_trie rr_NXT = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t001e };
static ldh_trie rr_NX = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL,&rr_NXT, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_N = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_NA, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL,&rr_NI, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL,&rr_NS, NULL, NULL, NULL, NULL,&rr_NX,
	  NULL, NULL }, NULL };
static ldh_trie rr_OPENPGPKEY = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t003d };
static ldh_trie rr_OPENPGPKE = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &rr_OPENPGPKEY, NULL }, NULL };
static ldh_trie rr_OPENPGPK = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL,&rr_OPENPGPKE, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_OPENPGP = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_OPENPGPK, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_OPENPG = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL,&rr_OPENPGP, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_OPENP = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL,&rr_OPENPG, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_OPEN = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL,&rr_OPENP, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_OPE = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &rr_OPEN, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_OP = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL,&rr_OPE, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_O = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL,&rr_OP, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_PTR = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t000c };
static ldh_trie rr_PT = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL,&rr_PTR, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_PX = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t001a };
static ldh_trie rr_P = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL,&rr_PT, NULL, NULL, NULL,&rr_PX,
	  NULL, NULL }, NULL };
static ldh_trie rr_RP = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0011 };
static ldh_trie rr_RRSIG = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t002e };
static ldh_trie rr_RRSI = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL,&rr_RRSIG, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_RRS = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL,&rr_RRSI, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_RR = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL,&rr_RRS, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_RT = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0015 };
static ldh_trie rr_R = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL,&rr_RP, NULL,&rr_RR, NULL,&rr_RT, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_SIG = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0018 };
static ldh_trie rr_SI = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL,&rr_SIG, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_SMIMEA = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0035 };
static ldh_trie rr_SMIME = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_SMIMEA,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_SMIM = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL,&rr_SMIME, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_SMI = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_SMIM,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_SM = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL,&rr_SMI, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_SOA = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0006 };
static ldh_trie rr_SO = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_SOA, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_SPF = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0063 };
static ldh_trie rr_SP = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL,&rr_SPF, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_SRV = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0021 };
static ldh_trie rr_SR = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_SRV, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_SSHFP = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t002c };
static ldh_trie rr_SSHF = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL,&rr_SSHFP, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_SSH = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL,&rr_SSHF, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_SS = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL,&rr_SSH, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_S = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL,&rr_SI, NULL, NULL, NULL,&rr_SM,
	  NULL,&rr_SO,&rr_SP, NULL,&rr_SR,&rr_SS, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_TLSA = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0034 };
static ldh_trie rr_TLS = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_TLSA,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_TL = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL,&rr_TLS, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_TXT = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0010 };
static ldh_trie rr_TX = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL,&rr_TXT, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_T = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_TL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_TX,
	  NULL, NULL }, NULL };
static ldh_trie rr_URI = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0100 };
static ldh_trie rr_UR = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL,&rr_URI, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_U = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL,&rr_UR, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_WKS = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t000b };
static ldh_trie rr_WK = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL,&rr_WKS, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_W = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_WK, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_X25 = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t0013 };
static ldh_trie rr_X2 = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_X25, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_X = {
	{ NULL, NULL, NULL, NULL, NULL,&rr_X2, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_ZONEMD = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, &t003f };
static ldh_trie rr_ZONEM = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL,&rr_ZONEMD, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_ZONE = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &rr_ZONEM, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL }, NULL };
static ldh_trie rr_ZON = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL,&rr_ZONE, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL }, NULL };
static ldh_trie rr_ZO = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	 &rr_ZON, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_Z = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL,&rr_ZO, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL }, NULL };
static ldh_trie rr_ldh_trie = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,&rr_A, NULL,
	 &rr_C,&rr_D,&rr_E, NULL,&rr_G,&rr_H,&rr_I, NULL,&rr_K,&rr_L,&rr_M,&rr_N,&rr_O,
	 &rr_P, NULL,&rr_R,&rr_S,&rr_T,&rr_U, NULL,&rr_W,&rr_X, NULL,&rr_Z }, NULL };
static dnsextlang_def p_dns_default_rrtypes = {
	(void *)rrtypes_table, &rr_ldh_trie, NULL };
dnsextlang_def *dns_default_rrtypes = &p_dns_default_rrtypes;
const dnsextlang_stanza *dnsextlang_lookup__(
    const char *s, size_t len, return_status *st)
{
	int t;
	const dnsextlang_stanza *r;
	
	switch (len) {
	case  1: switch (s[0]) {
	         case 'A': 
	         case 'a': return &t0001;
	         };
	         break;
	case  2: switch (s[0]) {
	         case 'N': 
	         case 'n': switch (s[1]) {
	                   case 'S': 
	                   case 's': return &t0002;
	                   };
	                   break;
	         case 'D': 
	         case 'd': switch (s[1]) {
	                   case 'S': 
	                   case 's': return &t002b;
	                   };
	                   break;
	         case 'M': 
	         case 'm': switch (s[1]) {
	                   case 'X': 
	                   case 'x': return &t000f;
	                   case 'R': 
	                   case 'r': return &t0009;
	                   case 'G': 
	                   case 'g': return &t0008;
	                   case 'B': 
	                   case 'b': return &t0007;
	                   case 'F': 
	                   case 'f': return &t0004;
	                   case 'D': 
	                   case 'd': return &t0003;
	                   };
	                   break;
	         case 'A': 
	         case 'a': switch (s[1]) {
	                   case '6': return &t0026;
	                   };
	                   break;
	         case 'L': 
	         case 'l': switch (s[1]) {
	                   case 'P': 
	                   case 'p': return &t006b;
	                   };
	                   break;
	         case 'K': 
	         case 'k': switch (s[1]) {
	                   case 'X': 
	                   case 'x': return &t0024;
	                   };
	                   break;
	         case 'P': 
	         case 'p': switch (s[1]) {
	                   case 'X': 
	                   case 'x': return &t001a;
	                   };
	                   break;
	         case 'R': 
	         case 'r': switch (s[1]) {
	                   case 'T': 
	                   case 't': return &t0015;
	                   case 'P': 
	                   case 'p': return &t0011;
	                   };
	                   break;
	         };
	         break;
	case  4: switch (s[0]) {
	         case 'A': 
	         case 'a': if (strncmp(s + 1, "AAA", 3)) break;
	                   return &t001c;
	         case 'N': 
	         case 'n': switch (s[1]) {
	                   case 'S': 
	                   case 's': switch (s[2]) {
	                             case 'E': 
	                             case 'e': switch (s[3]) {
	                                       case 'C': 
	                                       case 'c': return &t002f;
	                                       };
	                                       break;
	                             case 'A': 
	                             case 'a': switch (s[3]) {
	                                       case 'P': 
	                                       case 'p': return &t0016;
	                                       };
	                                       break;
	                             };
	                             break;
	                   };
	                   break;
	         case 'C': 
	         case 'c': if (strncmp(s + 1, "ERT", 3)) break;
	                   return &t0025;
	         case 'T': 
	         case 't': if (strncmp(s + 1, "LSA", 3)) break;
	                   return &t0034;
	         case 'G': 
	         case 'g': if (strncmp(s + 1, "POS", 3)) break;
	                   return &t001b;
	         case 'I': 
	         case 'i': if (strncmp(s + 1, "SDN", 3)) break;
	                   return &t0014;
	         };
	         break;
	case  3: switch (s[0]) {
	         case 'P': 
	         case 'p': if (strncmp(s + 1, "TR", 2)) break;
	                   return &t000c;
	         case 'T': 
	         case 't': if (strncmp(s + 1, "XT", 2)) break;
	                   return &t0010;
	         case 'S': 
	         case 's': switch (s[1]) {
	                   case 'R': 
	                   case 'r': switch (s[2]) {
	                             case 'V': 
	                             case 'v': return &t0021;
	                             };
	                             break;
	                   case 'O': 
	                   case 'o': switch (s[2]) {
	                             case 'A': 
	                             case 'a': return &t0006;
	                             };
	                             break;
	                   case 'P': 
	                   case 'p': switch (s[2]) {
	                             case 'F': 
	                             case 'f': return &t0063;
	                             };
	                             break;
	                   case 'I': 
	                   case 'i': switch (s[2]) {
	                             case 'G': 
	                             case 'g': return &t0018;
	                             };
	                             break;
	                   };
	                   break;
	         case 'C': 
	         case 'c': switch (s[1]) {
	                   case 'A': 
	                   case 'a': switch (s[2]) {
	                             case 'A': 
	                             case 'a': return &t0101;
	                             };
	                             break;
	                   case 'D': 
	                   case 'd': switch (s[2]) {
	                             case 'S': 
	                             case 's': return &t003b;
	                             };
	                             break;
	                   };
	                   break;
	         case 'U': 
	         case 'u': if (strncmp(s + 1, "RI", 2)) break;
	                   return &t0100;
	         case 'L': 
	         case 'l': switch (s[1]) {
	                   case '6': switch (s[2]) {
	                             case '4': return &t006a;
	                             };
	                             break;
	                   case '3': switch (s[2]) {
	                             case '2': return &t0069;
	                             };
	                             break;
	                   case 'O': 
	                   case 'o': switch (s[2]) {
	                             case 'C': 
	                             case 'c': return &t001d;
	                             };
	                             break;
	                   };
	                   break;
	         case 'N': 
	         case 'n': switch (s[1]) {
	                   case 'I': 
	                   case 'i': switch (s[2]) {
	                             case 'D': 
	                             case 'd': return &t0068;
	                             };
	                             break;
	                   case 'X': 
	                   case 'x': switch (s[2]) {
	                             case 'T': 
	                             case 't': return &t001e;
	                             };
	                             break;
	                   };
	                   break;
	         case 'D': 
	         case 'd': if (strncmp(s + 1, "LV", 2)) break;
	                   return &t8001;
	         case 'H': 
	         case 'h': if (strncmp(s + 1, "IP", 2)) break;
	                   return &t0037;
	         case 'A': 
	         case 'a': if (strncmp(s + 1, "PL", 2)) break;
	                   return &t002a;
	         case 'K': 
	         case 'k': if (strncmp(s + 1, "EY", 2)) break;
	                   return &t0019;
	         case 'X': 
	         case 'x': if (strncmp(s + 1, "25", 2)) break;
	                   return &t0013;
	         case 'W': 
	         case 'w': if (strncmp(s + 1, "KS", 2)) break;
	                   return &t000b;
	         };
	         break;
	case  5: switch (s[0]) {
	         case 'C': 
	         case 'c': switch (s[1]) {
	                   case 'N': 
	                   case 'n': if (strncmp(s + 2, "AME", 3)) break;
	                             return &t0005;
	                   case 'S': 
	                   case 's': if (strncmp(s + 2, "YNC", 3)) break;
	                             return &t003e;
	                   };
	                   break;
	         case 'R': 
	         case 'r': if (strncmp(s + 1, "RSIG", 4)) break;
	                   return &t002e;
	         case 'N': 
	         case 'n': switch (s[1]) {
	                   case 'S': 
	                   case 's': if (strncmp(s + 2, "EC3", 3)) break;
	                             return &t0032;
	                   case 'A': 
	                   case 'a': if (strncmp(s + 2, "PTR", 3)) break;
	                             return &t0023;
	                   };
	                   break;
	         case 'D': 
	         case 'd': switch (s[1]) {
	                   case 'N': 
	                   case 'n': if (strncmp(s + 2, "AME", 3)) break;
	                             return &t0027;
	                   case 'H': 
	                   case 'h': if (strncmp(s + 2, "CID", 3)) break;
	                             return &t0031;
	                   };
	                   break;
	         case 'E': 
	         case 'e': switch (s[1]) {
	                   case 'U': 
	                   case 'u': switch (s[2]) {
	                             case 'I': 
	                             case 'i': switch (s[3]) {
	                                       case '6': switch (s[4]) {
	                                                 case '4': return &t006d;
	                                                 };
	                                                 break;
	                                       case '4': switch (s[4]) {
	                                                 case '8': return &t006c;
	                                                 };
	                                                 break;
	                                       };
	                                       break;
	                             };
	                             break;
	                   };
	                   break;
	         case 'S': 
	         case 's': if (strncmp(s + 1, "SHFP", 4)) break;
	                   return &t002c;
	         case 'A': 
	         case 'a': if (strncmp(s + 1, "FSDB", 4)) break;
	                   return &t0012;
	         case 'M': 
	         case 'm': if (strncmp(s + 1, "INFO", 4)) break;
	                   return &t000e;
	         case 'H': 
	         case 'h': if (strncmp(s + 1, "INFO", 4)) break;
	                   return &t000d;
	         };
	         break;
	case  6: switch (s[0]) {
	         case 'D': 
	         case 'd': if (strncmp(s + 1, "NSKEY", 5)) break;
	                   return &t0030;
	         case 'Z': 
	         case 'z': if (strncmp(s + 1, "ONEMD", 5)) break;
	                   return &t003f;
	         case 'S': 
	         case 's': if (strncmp(s + 1, "MIMEA", 5)) break;
	                   return &t0035;
	         };
	         break;
	case  7: if (strncmp(s, "CDNSKEY", 7)) break;
	         return &t003c;
	case  8: switch (s[0]) {
	         case 'I': 
	         case 'i': if (strncmp(s + 1, "PSECKEY", 7)) break;
	                   return &t002d;
	         case 'N': 
	         case 'n': if (strncmp(s + 1, "SAP-PTR", 7)) break;
	                   return &t0017;
	         };
	         break;
	case 10: switch (s[0]) {
	         case 'N': 
	         case 'n': if (strncmp(s + 1, "SEC3PARAM", 9)) break;
	                   return &t0033;
	         case 'O': 
	         case 'o': if (strncmp(s + 1, "PENPGPKEY", 9)) break;
	                   return &t003d;
	         };
	         break;
	};
	if ((t = dnsextlang_get_TYPE_rrtype(s, len, st)) < 0)
		return NULL;
	
	if ((r = dnsextlang_get_stanza_(dns_default_rrtypes, t)))
		return r;
	
	(void) RETURN_NOT_FOUND_ERR(st, "rrtype not found");
	return NULL;
	
}
