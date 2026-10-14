#version 330 core
out vec4 FragColor;

float width = 800;
float height = 600;

struct Complex
{
    float real;
    float imaginary;
};

Complex mul(Complex c1, Complex c2)
{
    return Complex(
        c1.real * c2.real - c1.imaginary * c2.imaginary,
        c1.real * c2.imaginary + c2.real * c1.imaginary
    );
}

Complex add(Complex c1, Complex c2)
{
    return Complex (
        c1.real + c2.real,
        c1.imaginary + c2.imaginary
    );
}

float mag2(Complex c)
{
    return c.real * c.real + c.imaginary * c.imaginary;
}

struct EscapeData
{
    bool escaped;
    int num_iter;
};

EscapeData mandelbrot(Complex c)
{
    #define MAX_ITER 1000
    #define ESCAPE_RADIUS 4.0f

    Complex z = Complex(0.0f, 0.0f);
    EscapeData res = EscapeData(false, 0);

    for (int i = 0; i < MAX_ITER; ++i)
    {
        if (mag2(z) > ESCAPE_RADIUS)
        {
            res.escaped = true;
            res.num_iter = i;
            break;
        }

        z = add(mul(z, z), c);
    }

    return res;

    #undef MAX_ITER
    #undef ESCAPE_RADIUS
}

void main()
{
    float x_ndc = gl_FragCoord.x / width;
    float y_ndc = (height - gl_FragCoord.y) / height;

    EscapeData data = mandelbrot(Complex(x_ndc * 3.5f - 2.5f, y_ndc * 2.0f - 1));

    if (data.escaped)
    {
        float factor = sqrt(float(data.num_iter) / 1000);

        FragColor = vec4(0.0f, 0.0f, factor, 1.0f);
    }
    else
    {
        FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }
} 