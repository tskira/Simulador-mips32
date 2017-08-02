/*
 * TRABALHO 1 DE ARQII
 * ALUNO: THIAGO KIRA
 * PROFESSOR: ANDERSON
 * IMPLEMENTACAO DO SIMULADOR PARA MIPS32
 * GCC 6.3
 * FLEX 2.5.4
 * BISON 3.0.4
 * SO: UBUNTU 17.04
 *
 * MODO DE EXECUTAR:
 * $make
 * O simulador apresenta dois tipos de execucao:
 *
 * para modo simplificado (flag -s)
 * $./simulador -s "arquivo_mips" "numero de clocks"
 *
 * EXEMPLO: $./simulador -s 1.asm 45
 *
 * arquivo_mips: nome do arquivo contendo codigo mips a ser executado
 * numero de clocks: numero de clocks em que se deseja parar a execucao
 *
 * para modo detalhado (flag -d)
 * $./simulador -d "arquivo_mips" "numero de clocks"
 *
 *  * EXEMPLO: $./simulador -d 1.asm
 *
 * O arquivo 1.asm e pega um vetor da memoria e multiplica por 2, salvando nos registradors $s0 .. $s4
 * O arquivo 2.asm semelhante ao 1, porem apos realizar o calculo armeza o valor de volta na memoria e
 * em seguida salva nos registradores $t0 ... $t4
 * O arquivo 3.asm testa os jal e jr
 */
