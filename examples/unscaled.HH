in="/bob/data/saltf@@"
n1=676 n2=676 n3=210
o1=0.0 o2=0.0 o3=0.0
d1=20.0 d2=20.0 d3=20.0
esize=4


Transp:   bob@kana   Sun Jul  6 10:57:08 1997
		sepstr_ready_out() : sets next in="stdin"
#	Creating work file /scrka1/bob/Transpa001Ft
# Transp: input n1=676  n2=676  n3=210 esize=4
#		o2=0.000000 o3=0.000000
#		d2=20.000000 d3=20.000000
Transp: output n1=676  n2=210  n3=676 esize=4
		o2=0.000000 o3=0.000000
		d2=20.000000 d3=20.000000
#	output tag is "out" 
		data_format="xdr_float"


Transp:   bob@kana   Sun Jul  6 10:57:08 1997
		sets next: in="/scrka1/bob/vel_trans.H@"
#	Creating work file /scrka1/bob/Transpa001FY
# Transp: input n1=676  n2=210  n3=676 esize=4
#		o1=0.000000 o2=0.000000
#		d1=20.000000 d2=20.000000
Transp: output n1=210  n2=676  n3=676 esize=4
		o1=0.000000 o2=0.000000
		d1=20.000000 d2=20.000000
#	output tag is "out" 
		data_format="xdr_float"



/bob/bin/SGI64/spike.x:   bob@kana   Sun Jul  6 11:32:49 1997
		sets next: in="/scrka1/bob/junk1.H@"
		From history: d1=20
		From history: n1=210
		From history: n2=676
		From history: n3=676
		From history: esize=4
		From par: max_search=3
#	output tag is "out" 
		data_format="xdr_float"


/bob/bin/SGI64/despike2.x:   bob@kana   Sun Jul  6 11:35:16 1997
		sets next: in="/scrka1/bob/despike.H@"
		From history: n1=210
		From history: n2=676
		From history: n3=676
		From par: size=3
		From par: invert=1
#	output tag is "out" 
		data_format="xdr_float"


/bob/bin/SGI64/background.x:   bob@kana   Sun Jul  6 16:18:10 1997
		sets next: in="/scrka1/bob/background.H@"
		From par: low2=80
		From par: low3=100
		From par: high2=570
		From par: high3=620
		From history: n1=210
		From history: n2=676
		From history: n3=676
		n1=2
		n2=5
		n3=21
#	output tag is "out" 
		data_format="xdr_float"


Cp:   bob@kana   Mon Jul  7 14:37:43 1997
		sepstr_ready_out() : sets next in="stdin"
#	output tag is "out" 
		data_format="xdr_float"

:.�4:.��:.�:&q
:":!��:!�: �L: �:RV:�:�:v�:[:|�:��:�:M:�":�:1�:�:
Ԫ:
'�:	}�:�m:/S:��:�:J:�z::u:��:Dv:�x:�:��: ��: m^9���9���9���9�v�9�j9�\x9�Q�9�L9�I�9�I�9�K[9�NV9�V�9�`�9�m%9�z�999��9���9���9�$9�$+9�Hh9�l+9�"9�(9��%9��9�@d9�n{9�89���9�	9�C<9�|j9޸�9��Q9�3�9�w+9۹!9���9�DD9ٌn9��y9�"9�p�9־*9��9�au9Բ�9�	9�`�9ҸY9��9�n�9���9�(q9ωF9���9�JL9ͭc9�9�x�9�� 9�HN9ʳ9��9ɌO9��F9�h�9�م9�Nm9�Ƈ9�F9�ϩ9�h�9�`9��x9��\9�$9�c�9�Q9���9�.9�PZ9�9�0�9͋f9��9���9���9�\|9��?9�o�9��9�V�9Ӕ�9ӵ^9�˥9��<9�.�9ԙ�9�4�9���9�w�9���9��39��9���9ք9�4�9�ъ9�_y9��9�a�9�֡9�KJ9��:9�8C9ѰP9�*9Ф�9��9Ϝi9��9Θ99��9͘9�-9̜9��9ˤ�9�*9ʰ�9�8A9��>9�I9��v9�_�9�`9�`9�`i9Ӣ�9Ӣ�9Ӣ�9Ӣ�9Ӣ�9Ӣ�9Ӣ�9Ӣ�9Ӣ�9Ӣ�9Ӣ�9Ӣ�9Ӣ�9Ӣ�9Ӣ�9Ӣ�9Ӣ�9Ӣ�9Ӣ�9Ӣ�9Ӣ�9Ӣ�9Ӣ�9Ӣ�9Ӣ�9Ӣ�9Ӣ�