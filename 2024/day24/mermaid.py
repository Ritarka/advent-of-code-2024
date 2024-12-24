def process_logic_gates(gates):
    # Split the input into lines
    lines = gates.strip().split("\n")
    
    for line in lines:
        a, op, b, arr, c = line.split()
        if a > b:
            a, b = b, a
        line = "".join([a, op, b, arr, c])
    
    # Sort the lines alphabetically
    sorted_lines = sorted(lines)
    
    # Format for Graphviz (DOT format)
    graphviz_output = "digraph G {\n"
    gate_count = 0
    
    for line in sorted_lines:
        left, right = line.split("->")
        left = left.strip()
        right = right.strip()
        
        if "AND" in left or "OR" in left or "XOR" in left:
            parts = left.split()
            node1, op, node2 = parts[0], parts[1], parts[2]
            gate_node = f"gate{gate_count} [label=\"{op}\"]"
            gate_count += 1
            
            graphviz_output += f"    {node1} -> {op}{gate_count}\n"
            graphviz_output += f"    {node2} -> {op}{gate_count}\n"
            graphviz_output += f"    {op}{gate_count} -> {right}\n"
        else:
            graphviz_output += f"    {left} -> {right}\n"
    
    graphviz_output += "}"
    return graphviz_output

gates = """
vpn AND wjg -> rcr
y25 AND x25 -> sdn
ncs XOR vnn -> z31
dtn OR tvq -> jsb
vjv XOR ddg -> z16
x06 AND y06 -> vdb
x04 AND y04 -> fkc
msh AND mkf -> nqq
y05 AND x05 -> qjc
dkp AND qwf -> dvn
jsb AND bmd -> rdk
y00 XOR x00 -> z00
y35 XOR x35 -> khk
pcf AND dhr -> cjv
vqg AND hcc -> gbd
x39 AND y39 -> wgk
x33 XOR y33 -> vgr
bqj OR shf -> qvq
y21 AND x21 -> qvc
vqs XOR mpr -> z20
x04 XOR y04 -> vpn
y01 XOR x01 -> msh
wkq OR stf -> gmr
fgw XOR vgg -> z06
x01 AND y01 -> cjn
x11 AND y11 -> spp
nhd AND fns -> bhc
gdw XOR smg -> z03
qcn OR fhv -> gmd
dvn OR jqm -> tbt
x42 AND y42 -> jqm
y09 AND x09 -> cwr
rwv OR tfn -> ctt
gnq OR gbd -> wqn
tfj AND jwq -> mcp
gpg OR sdn -> bbg
y16 AND x16 -> nfb
tth XOR pdm -> z22
x08 AND y08 -> hdf
ppn AND qbn -> hph
dmf OR rvw -> ngm
vqg XOR hcc -> z12
hfj OR cbt -> wbr
cwd OR vvb -> gbj
x34 XOR y34 -> mgm
knk XOR ntf -> z18
x12 XOR y12 -> vqg
khf AND ngm -> rwv
fhn AND fcw -> vvb
gmr AND hqc -> chn
x12 AND y12 -> gnq
sfh OR wgk -> kmr
mkf XOR msh -> z01
fhn XOR fcw -> z14
fgm OR jts -> qwf
bpf OR qjc -> fgw
tbt XOR bhd -> z43
x16 XOR y16 -> vjv
x06 XOR y06 -> vgg
x03 AND y03 -> hwj
phv OR gwf -> bjp
gmd XOR dqm -> z23
y39 XOR x39 -> hqb
y20 XOR x20 -> vqs
jrs XOR qws -> z09
dfm XOR hnf -> z25
x15 XOR y15 -> ddr
y17 AND x17 -> bwr
rtb AND kqb -> hgj
vqf OR pqv -> gdw
y38 XOR x38 -> mpd
kks XOR wqn -> z13
ddg AND vjv -> gdv
x11 XOR y11 -> cgn
svd OR nfd -> z45
y44 AND x44 -> svd
twg AND tnm -> pqv
ntf AND knk -> ngh
fmj XOR vgr -> z33
cjh AND cgn -> skn
x07 XOR y07 -> fns
ddr AND gbj -> qcp
mwg XOR pbh -> z37
tbt AND bhd -> hfj
x28 AND y28 -> tfn
chn OR qcw -> dfm
y25 XOR x25 -> hnf
wbr XOR dfr -> z44
x24 AND y24 -> hqc
ctt XOR nqr -> z29
y10 XOR x10 -> dhr
x17 XOR y17 -> gqk
fdw OR chc -> tht
x02 XOR y02 -> twg
bbg XOR dnb -> z26
hdf OR mcp -> jrs
x22 AND y22 -> qcn
x27 AND y27 -> rvw
bwr OR dfh -> knk
y28 XOR x28 -> khf
pvd AND bjp -> fgm
tdv OR ngh -> kqb
x00 AND y00 -> mkf
dsb OR rnr -> tgs
mpd XOR qvq -> z38
tgs AND khk -> chc
y41 XOR x41 -> pvd
x09 XOR y09 -> qws
x34 AND y34 -> rnr
y37 XOR x37 -> pbh
qmn XOR jsh -> z27
vpn XOR wjg -> z04
x40 XOR y40 -> pkj
nsg OR nwn -> vjg
x35 AND y35 -> z35
crk OR cfs -> mwg
rcr OR fkc -> whh
gqk AND jkm -> dfh
x27 XOR y27 -> qmn
hph OR qvc -> tth
jtw OR bmp -> pgr
y29 AND x29 -> bmp
x22 XOR y22 -> pdm
x29 XOR y29 -> nqr
x36 AND y36 -> crk
y10 AND x10 -> rck
y03 XOR x03 -> smg
bbg AND dnb -> vpb
tnm XOR twg -> z02
rvp OR qjt -> fhn
cjv OR rck -> cjh
ngm XOR khf -> z28
qfs AND whh -> z05
hqb AND vjg -> sfh
skn OR spp -> z11
cwr OR mqg -> pcf
x44 XOR y44 -> dfr
hhw OR fgr -> vjb
kmr AND pkj -> gwf
x08 XOR y08 -> jwq
ppn XOR qbn -> z21
kqb XOR rtb -> z19
mgm XOR vjb -> z34
mpr AND vqs -> wcr
hqb XOR vjg -> z39
cgn XOR cjh -> hcc
y02 AND x02 -> vqf
ghv AND tht -> cfs
x13 XOR y13 -> kks
y26 XOR x26 -> dnb
qws AND jrs -> mqg
mgm AND vjb -> dsb
x26 AND y26 -> swb
x31 AND y31 -> tvq
x20 AND y20 -> bgk
kmn OR qcp -> ddg
y30 XOR x30 -> dtf
wcr OR bgk -> ppn
dkp XOR qwf -> z42
y15 AND x15 -> kmn
x38 AND y38 -> nsg
x21 XOR y21 -> qbn
dtf XOR pgr -> z30
x40 AND y40 -> phv
x32 AND y32 -> csk
y31 XOR x31 -> vnn
y24 XOR x24 -> qcw
pkj XOR kmr -> z40
gmr XOR hqc -> z24
x43 AND y43 -> cbt
y18 XOR x18 -> ntf
pgr AND dtf -> ppm
nqr AND ctt -> jtw
wqn AND kks -> rvp
x13 AND y13 -> qjt
jsb XOR bmd -> z32
qfs XOR whh -> bpf
y23 XOR x23 -> dqm
y33 AND x33 -> hhw
ncs AND vnn -> dtn
y19 XOR x19 -> rtb
rdk OR csk -> fmj
gdw AND smg -> bqg
x32 XOR y32 -> bmd
nqq OR cjn -> tnm
gbj XOR ddr -> z15
x05 XOR y05 -> qfs
bqg OR hwj -> wjg
x30 AND y30 -> hsh
y19 AND x19 -> wfc
tfj XOR jwq -> z08
x43 XOR y43 -> bhd
x42 XOR y42 -> dkp
fmj AND vgr -> fgr
y41 AND x41 -> jts
nhd XOR fns -> z07
qvq AND mpd -> nwn
jkm XOR gqk -> z17
tth AND pdm -> fhv
hsh OR ppm -> ncs
nfb OR gdv -> jkm
khk XOR tgs -> fdw
wbr AND dfr -> nfd
hgj OR wfc -> mpr
dfm AND hnf -> gpg
mwg AND pbh -> bqj
x14 AND y14 -> cwd
y37 AND x37 -> shf
y18 AND x18 -> tdv
dhr XOR pcf -> z10
vpb OR swb -> jsh
vgg AND fgw -> csf
qmn AND jsh -> dmf
x36 XOR y36 -> ghv
y23 AND x23 -> stf
dqm AND gmd -> wkq
y14 XOR x14 -> fcw
ghv XOR tht -> z36
hvc OR bhc -> tfj
bjp XOR pvd -> z41
csf OR vdb -> nhd
x07 AND y07 -> hvc
"""

print(process_logic_gates(gates))