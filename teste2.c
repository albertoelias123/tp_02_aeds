for (x = 1; x <= tamanhoArrayFinal; x++)
{
    if (somaCarga + demandaCidades[vetorAux[x - 1]] <= capacidadeCaminhao)
    {
        if (auxiliar != 0)
        {
            somaCarga += demandaCidades[auxiliar];
            array[x] = auxiliar;
            auxiliar = vetorAux[x - 1];
        }
        else
        {
            somaCarga += demandaCidades[vetorAux[x - 1]];
            array[x] = vetorAux[x - 1];
        }
    }
    else
    {
        somaCarga = 0;
        array[x] = 0;
        auxiliar = vetorAux[x - 1];
    }
    printf("\n arrayx: %d", array[x - 1]);
}