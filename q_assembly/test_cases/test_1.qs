Traditional assembly-like version:

gate PARAM_GATE = [
    gate g_0 = mul |0> <0|
    gate g_1 = mul |1> <1|
    gate first_half = combine g_0 I
    gate second_half = combine g_1 X
    @ = add first_half second_half
]

circuit algorithm_deutsch (gate PARAM_GATE):
    state register_0 = |0>
    state register_1 = |->

    register_0 = apply H register_0
    state combined = combine register_0 register_1
    combined = apply PARAM_GATE combined

    combined = apply H combined[0]

    qm_result result = meaure combined

    show result.state
    show result.value

    output result

-----------------------------------------------------------
Quantum circuit-like version:

PARAM_GATE (
    |0>*<0| @ (I) + |1>*<1| @ (X)
)

{
    {1 | 0}              ?? {|0>}
    {1/(#2) | -1/(#2)}   ?? {|->}  ?? {(H)|1>}
} 
    -> (H)[0]            ?? The same as: (H)[0] && (I)[1]
    -> (PARAM_GATE) 
    -> (H)[0] 
    -> <[0]