Neopixel displa( 64x WS2812B )
==============================


Komunikace s displejem
------------------------------------

```c
void init_tim(void){
    GPIO_Init(GPIOC,GPIO_PIN_1,GPIO_MODE_OUT_PP_LOW_FAST); // PC1 (TIM1_CH1)
    TIM1_TimeBaseInit(0, TIM1_COUNTERMODE_UP, 15, 0); // Upcounting, prescaler 0, dont care period/ARR value
    // OC1 as output with Polarity High in PWM2 mode (OC1N not used)
    TIM1_OC1Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_DISABLE,
                 1, TIM1_OCPOLARITY_HIGH, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_SET,
                 TIM1_OCNIDLESTATE_RESET);
    TIM1_CtrlPWMOutputs(ENABLE); // Timer output global enable
    TIM1_SelectOnePulseMode(TIM1_OPMODE_SINGLE); // Selecting One Pulse Mode
}
```
```c
void let_that_sink_in(uint32_t data[64]){

    uint8_t length = 64;
    uint32_t mask;
    disableInterrupts(); // can be omitted if interrupts do not take more then about ~25us
    while(length){   // for all bytes from input array
        length--;
        mask=0b100000000000000000000000; // for all bits in byte
        while(mask){
            while(TIM1->CR1 & TIM1_CR1_CEN); // wait if timer run (transmitting last bit)
            if(mask & data[length]){ // send pulse with coresponding length ("L" od "H")
                TIM1->ARRL = H_PULSE; // set pulse width for "H" bit
            }else{
                TIM1->ARRL = L_PULSE; // set pulse width for "L" bit
            }
            TIM1->CR1 |= TIM1_CR1_CEN; // Start timer (start single pulse generation)
            mask = mask >> 1;
        }
    }

    enableInterrupts();
}
```
Při odesílání si rozkouskuje data na jednotlivé bity a postupne podle nich zapisuje do registru pro tim1 
který na jejich zakladě generuje singlepulzy reprezentující 1/0 na onewire sběrnici pro WS2812B.
Každá led má buffer na 24bit => do ní zapisujeme barvu ve formátu  GRB `0xff00ff` každé dva digity reprezentují intenzitu jedné barvy.


Flow chart přepínání jednotlivých módů
------------------------------------
<div style="background-color: white; display: inline-block; padding: 10px;">
    <img src="./images/schema.svg" alt="Example Image" width="350">
</div>


Schéma

------------------------------------
<img src="./images/diagram.svg" alt="Example Image" width="350">

[SDCC-gas](https://github.com/XaviDCR92/sdcc-gas) vzniklo, aby vyřešilo problém
optimalizace mrtvého kódu přidáním podpory [GNU
Assembleru](https://cs.wikipedia.org/wiki/GNU_Assembler) tedy *gas* do SDCC
3.9.0. [gas](https://codedocs.org/what-is/gnu-assembler) je výhodou i nevýhodou
tohoto řešení. Na jednu stranu to znamená, že můžeme používat klasické nástroje
z [GNU binutils](https://cs.wikipedia.org/wiki/GNU_binutils), na druhou stranu
to znamená, že nelze použít ty části sdcc-libraries, které jsou napsané v STM8
assembleru a je nutné použít méně optimální kód napsaný v C nebo STM8 assembler
přepsat do GNU assembleru.

#### sdccrm

Toto řešení je jen jakýsi historický pozůstatek a v 99% případů ho
nepotřebujete a nechcete použít.

[sdccrm](https://github.com/XaviDCR92/sdccrm) je nástroj pro optimalizaci
mrtvého kódu vytvořeného SDCC, který odstraňuje nepoužívané funkce. Kód se
nejprve zkompiluje do assembleru klasickým SDCC, poté se pomocí sdccrm vymaže
kód, který se nepoužívá, celý proces se dokončí a kód se převede z assembleru
do strojového kódu. Z logiky věci toto řešení vylučuje použití debugeru.

Dále **je nutné** ručně zadat/editovat funkce, které nechcete optimalizovat –-
tedy vyhodit. Proto je třeba sledovat chybová hlášení a název chybějící funkce
zadat do souboru `exclude_reference` uvnitř projektového adresáře.



Použití
--------------

Nejprve je třeba v `Makefile` správně nastavit µprocesor a jeho frakvenci;
případně cestu k instalaci SDCC
[STVP](https://www.st.com/en/development-tools/stvp-stm8.html).

```make
#DEVICE_FLASH=stm8s103f3
DEVICE_FLASH=stm8s208rb

### STlink version for falsh2 targer (stm8flash program)
#STLINK=stlinkv2
#STLINK=stlink
STLINK=stlinkv21

F_CPU=16000000

ifeq ($(OS),Windows_NT)
	CC_ROOT = "/c/Program Files/SDCC"
	STVP_ROOT = "/c/Program Files (x86)/STMicroelectronics/st_toolset/stvp"
else
	CC_ROOT = /usr
endif
```

Pokud používáte `sdccrm` je ještě potřebné v `Makefile` odkomentovat nebo
zakomentovat nebo přidat ty části SPL knihovny, které zrovna (ne)používáte.

```make
SPL_SOURCE  = stm8s_gpio.c stm8s_clk.c stm8s_tim4.c stm8s_itc.c 
SPL_SOURCE += stm8s_uart1.c
#SPL_SOURCE += stm8s_adc2.c
#SPL_SOURCE += stm8s_tim1.c
SPL_SOURCE += stm8s_tim2.c
#SPL_SOURCE += stm8s_tim3.c
```

... no a potom už jen bastlíte, programujete a voláte `make`.

Pokud používáte `sdcc-gas` budete možná muset vytvořit pro váš µprocesor
linker-script. Jsou to soubory s příponou `*.x` v adresáři `.make`. Tento
toolchain *zatím* obsahuje pouze linker-scripty pro µprocesory:  `stm8s003f3`,
`stm8s103f3` a `stm8s208rb`. Pokud tak učiníte, jistě mi jej zašlete k zařazení
do tohoto toolchainu.

| příkaz&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;||
|:---------- |:--------------------------- |
| `make spl` | stáhne a nachystá knihovny |
| `make` | provede kompilaci |
| `make flash` | nahraje program do chipu. Na Linuxu se použije [OpenOCD](https://openocd.org/). Na Windows se použije [STVP](https://www.st.com/en/development-tools/stvp-stm8.html) verze pro příkazový řádek.|
| `make flash2` | záložní varianta, protože OpenOCD někdy nechce čip naprogramovat (používá [stm8flash](https://github.com/vdudouyt/stm8flash)).
| `make clean` | smaže všechno, co nakompiloval
| `make rebuild` | smaže vše a znovu zkompiluje
| `make openocd` | pustí `openocd` pro debug
| `make debug` | spustí STM8-gdb


Závislosti
---------------

* [GNU Make](https://www.gnu.org/software/make/)
* [GNU Bash](https://www.gnu.org/software/bash/) -- ten se na Windows
  dá nainstalovat společně s [Git](https://git-scm.com/download/win)em.
* [SDCC](http://sdcc.sourceforge.net/)
  nebo [SDCC-gas](https://github.com/XaviDCR92/sdcc-gas)
* [STM8 binutils](https://stm8-binutils-gdb.sourceforge.io) (`stm8-gdb`, `stm8-ln`)
* [OpenOCD](https://openocd.org/) pro `flash` a `debug`
  nebo [STVP](https://www.st.com/en/development-tools/stvp-stm8.html)
  pro `flash` na Windows.
* ([stm8flash](https://github.com/vdudouyt/stm8flash) pro `flash2`)

### Na Windows

[`choco`](https://chocolatey.org/)` install git make vscode mingw`

