#!/usr/bin/env python

n_by_name = dict()
def get_len_names():
	sz = 0
	with file('rrtypes.order') as f:
		names = list()
		for ln in f:
			name, number = ln.strip().split()
			n_by_name[name] = number
			if len(name) != sz:
				if names:
					yield sz, names
				sz = len(name)
				names = list()
			names.append((name, int(number)))
		yield sz, names


def make_switch(i, names, indent):
	if len(names) == 1 and len(names[0][0]) != 1:
		if len(names[0][0]) == 0:
			return "return &t%.4x;" % names[0][1]
		if len(names[0][0]) == 1 and names[0][0].isalpha():
			return ( "if (s[%d] != '%s'\n%s" 
			       + "&&  s[%d] != '%s') break;\n%s"
			       + "return &t%.4x;" ) \
			       % ( i, names[0][0], ' ' * indent
			         , i, names[0][0].lower(), ' ' * indent
				    , names[0][1])
		if len(names[0][0]) == 1:
			return ( "if (s[%d] != '%s') break;\n%s"
			       + "return &t%.4x;" ) \
			       % ( i, names[0][0], ' ' * indent, names[0][1])

		s = ('s + %d' % i) if i else 's'
		return ( 'if (strncmp(%s, "%s", %d)) break;\n%s'
		       + "return &t%.4x;" ) \
		       % ( s, names[0][0], len(names[0][0])
		         , ' ' * indent, names[0][1])
	ret = 'switch (s[%d]) {' % i
	ch = ''
	prevs = set()
	for name, number in names:
		if name[0] != ch:
			ret += '\n' + ' ' * indent
			ret += "case '%s': " % name[0]
			if name[0].lower() != name[0]:
				ret += '\n' + ' ' * indent
				ret += "case '%s': " % name[0].lower()
			ch = name[0]
			assert(ch not in prevs)
			prevs.add(ch)
			sel = [(x[1:], y) for x, y, in names if x.startswith(ch)]
			ret += make_switch(i + 1, sel, indent + 10)
	ret += '\n' + ' ' * indent
	#ret += 'default : break;'
	#ret += '\n' + ' ' * indent
	ret += '};\n' + ' ' * indent
       	ret += 'break;'
	return ret
		

text = 'switch (len) {'
for ln, names in get_len_names():
	text += '\ncase %2d: ' % ln
	text += make_switch(0, names, 9)
text += """
};
return NULL;
"""

print """ 
static const dnsextlang_stanza *p_dnsextlang_lookup_(
    const char *s, size_t len)
{"""
for ln in text.split('\n'):
	print '\t' + ln
print """}

const dnsextlang_stanza *dnsextlang_lookup_(
    const char *s, size_t len, return_status *st)
{
	const dnsextlang_stanza *r;
	int t;
	
	if ((r = p_dnsextlang_lookup_(s, len)))
		return r;

	if ((t = dnsextlang_get_TYPE_rrtype(s, len, st)) < 0)
		return NULL;
	
	if ((r = dnsextlang_get_stanza_(dns_default_rrtypes, t)))
		return r;
	
	(void) RETURN_NOT_FOUND_ERR(st, "rrtype not found");
	return NULL;
}

int dnsextlang_get_type_(const char *s, size_t len, return_status *st)
{
	const dnsextlang_stanza *r;

	if ((r = p_dnsextlang_lookup_(s, len)))
		return r->number;

	return dnsextlang_get_TYPE_rrtype(s, len, st);
}
"""

