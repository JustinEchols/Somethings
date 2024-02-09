// NOTE(Justin): The hexadecimal representation of fp inf is 0x7f800000.
// Similarly the hexadecimaal representation of fp -inf is 0xff800000;
// Taken from https://www.h-schmidt.net/FloatConverter/IEEE754.html


// Trick for getting +- inf. First, store the hex value as u32. 
// Then return it as a f32.
function f32 
F32Min(void)
{
	u32 inf = 0x7f800000;
	f32 *p = (f32 *)&inf;
	return(*p);
}

function f32
F32MinNegative(void)
{
	u32 neg_inf = 0xff800000;
	f32 *p = (f32 *)&neg_inf;
	return(*p);
}

function f64
F64Min(void)
{

}

function f64
F64MinNegatiwe(void)
{

}
