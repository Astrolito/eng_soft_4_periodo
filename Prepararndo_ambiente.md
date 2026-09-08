# Engenharia de Software - 4o periodo

Material de aulas e exercicios organizado por linguagem:

- `C++/`: exemplos em C/C++ sobre listas estaticas, listas dinamicas e pilhas.
- `Java/`: exemplos e testes em Java.
- `Python/`: aulas e listas de exercicios em Python.
- `Sql/`: modelagem, comandos SQL e atividades de banco de dados.

## Requisitos do sistema

Instale os seguintes componentes antes de configurar os kernels:

- **VS Code**.
- Extensoes **Jupyter** e **Python** da Microsoft para abrir e executar notebooks.
- Extensao **C/C++** da Microsoft para compilar os arquivos `.c` e `.C`.
- Extensao **Extension Pack for Java** para editar e executar Java.
- Python 3.10 ou superior, com `venv` e `pip`.
- GCC/G++ para os exemplos em C/C++.
- JDK, incluindo `javac`, para os exemplos em Java.
- Conda ou Mamba, recomendado para instalar kernels Jupyter de C/C++ e Java.

No Ubuntu/Debian, a base pode ser instalada com:

```bash
sudo apt update
sudo apt install python3 python3-venv python3-pip build-essential openjdk-17-jdk
```

O projeto foi verificado em um ambiente Linux com Python 3.14, GCC 15 e OpenJDK 25. Versoes LTS do Java, como JDK 17 ou 21, tendem a oferecer maior compatibilidade com extensoes e kernels.

## Preparar o ambiente Python

Na raiz do repositorio, crie um ambiente virtual e instale o kernel Python:

```bash
python3 -m venv .venv
source .venv/bin/activate
python -m pip install --upgrade pip
python -m pip install jupyterlab notebook ipykernel ipython-sql sqlalchemy pandas matplotlib numpy
python -m ipykernel install --user --name eng-soft-python --display-name "Python (eng-soft-4-periodo)"
```

O ambiente Python e usado pelos notebooks de `Python/` e tambem pelos notebooks de `Sql/` que possuem kernel `python`, `python3` ou `python-dev`.

Para verificar a instalacao:

```bash
python --version
python -m jupyter --version
python -m jupyter kernelspec list
```

O kernel `python-dev` aparece em alguns metadados antigos deste repositorio, mas e um nome local e pode nao existir em outra maquina. Se ele nao aparecer, selecione `Python (eng-soft-4-periodo)` no VS Code.

## Configurar o VS Code

1. Abra a pasta raiz `eng_soft_4_periodo` no VS Code.
2. Abra um arquivo `.ipynb`.
3. Clique em **Select Kernel** no canto superior direito.
4. Escolha o kernel correspondente na lista.
5. Execute uma celula com o botao de executar ou com `Shift+Enter`.

Para notebooks que nao possuem `kernelspec` no arquivo, a escolha do kernel precisa ser feita manualmente. Essa escolha fica associada ao notebook no ambiente do VS Code, mas nao necessariamente altera o arquivo compartilhado.

## Kernel Python

Use `Python (eng-soft-4-periodo)` para:

- `Python/Aula_python_17_08_26.ipynb`
- `Python/Aula_python_24_08_26.ipynb`
- `Python/Aula_python_31_08_26.ipynb`
- `Python/Lista_Exercicios_01.ipynb`
- notebooks de `Sql/`, salvo se voce tiver um ambiente especifico para banco de dados.

Os notebooks Python analisados nao exigem uma biblioteca externa obrigatoria para as celulas basicas. As bibliotecas instaladas acima cobrem analise de dados, graficos e os comandos `%sql` usados nos exemplos de banco.

## Kernel C/C++

Os notebooks `C++/aula_20_08_Listas.ipynb`, `C++/aula_27_08_listas_dinamicas.ipynb` e `C++/teste.ipynb` declaram o kernel `c`. Esse kernel nao faz parte da instalacao padrao do Jupyter. Uma opcao pratica e instalar o `xeus-cling` em um ambiente Conda:

```bash
conda create -n eng-soft-cpp -c conda-forge xeus-cling jupyterlab
conda activate eng-soft-cpp
jupyter kernelspec list
```

O `xeus-cling` normalmente registra um kernel C++ com nome diferente de `c`. No VS Code, selecione o kernel C++/Cling disponivel. Se o notebook exigir exatamente o nome `c` e ele nao aparecer, abra as celulas como referencia ou copie o codigo para um arquivo `.c` e compile pelo terminal:

```bash
gcc -Wall -Wextra -std=c11 C++/teste.c -o /tmp/teste
/tmp/teste
```

Para o arquivo `C++/AULA.C`:

```bash
gcc -Wall -Wextra -std=c11 -x c C++/AULA.C -o /tmp/lista-dinamica
/tmp/lista-dinamica
```

O argumento `-x c` e necessario neste arquivo porque o GCC costuma interpretar a extensao maiuscula `.C` como C++.

O arquivo `.vscode/tasks.json` ja possui uma tarefa para compilar o arquivo C/C++ ativo com GCC. Abra o arquivo, use **Terminal > Run Build Task** e escolha `C/C++: gcc build active file`.

O notebook `C++/Aula_03_09_Pilhas.ipynb` atualmente contem apenas Markdown. Ele pode ser lido sem kernel; para adicionar celulas executaveis, selecione C++/Cling ou use um arquivo `.c` separado.

## Kernel Java

`Java/teste.ipynb` declara o kernel `java`. Para executar Java dentro de um notebook, instale um kernel Jupyter compatível, como o IJava. O procedimento de instalação pode variar conforme a versão do JDK e do release do IJava; depois da instalação, confirme:

```bash
jupyter kernelspec list
java --version
javac --version
```

No VS Code, selecione o kernel com nome ou descrição `Java`. Se o kernel Java ainda não estiver instalado, o arquivo pode ser compilado normalmente fora do notebook:

```bash
javac Java/SeuArquivo.java
java -cp Java SeuArquivo
```

O repositorio atualmente possui apenas `Java/teste.ipynb`, sem arquivos `.java` independentes.

## SQL e banco de dados

Os notebooks de `Sql/` nao usam um kernel SQL dedicado. Eles foram identificados como notebooks Python; `Sql/teste_banco.ipynb` usa a conexao:

```text
sqlite:///faculdade.db
```

Portanto, selecione `Python (eng-soft-4-periodo)` e instale o suporte SQL:

```bash
source .venv/bin/activate
python -m pip install ipython-sql sqlalchemy
```

O SQLite nao exige servidor separado. Uma conexao como `sqlite:///faculdade.db` cria ou abre o arquivo `faculdade.db` no diretorio de trabalho do notebook. Execute as celulas de criacao de tabelas antes das consultas.

Se aparecer `UsageError: Cell magic %%sql not found`, o pacote `ipython-sql` nao foi instalado no mesmo ambiente selecionado pelo notebook. Reative `.venv`, instale o pacote e selecione novamente o kernel Python.

## Executar pelo terminal

Com o ambiente Python ativo, e possivel iniciar o JupyterLab:

```bash
source .venv/bin/activate
python -m jupyter lab
```

Para executar um notebook inteiro e salvar uma copia do resultado:

```bash
python -m jupyter nbconvert --to notebook --execute \
  --ExecutePreprocessor.timeout=120 \
  --output /tmp/notebook-executado.ipynb \
  Python/Lista_Exercicios_01.ipynb
```

Essa execucao deve ser feita somente depois de selecionar um kernel e instalar as dependencias da pasta correspondente. Notebooks que dependem de entrada interativa ou de um banco criado em celulas anteriores podem precisar ser executados manualmente no VS Code.

## Diagnostico rapido

### O kernel nao aparece

```bash
python -m jupyter kernelspec list
```

Se o kernel Python nao aparecer, ative `.venv` e execute novamente `python -m ipykernel install --user --name eng-soft-python --display-name "Python (eng-soft-4-periodo)"`. Para C/C++ e Java, verifique os ambientes Conda e reinstale o kernel especifico.

### O notebook usa o kernel errado

Abra o seletor **Select Kernel** e escolha o ambiente correto. Para SQL, escolha Python; para C/C++, escolha C++/Cling; para Java, escolha Java.

### Uma celula falha por biblioteca ausente

Confirme o interpretador selecionado e instale o pacote nesse mesmo ambiente. No Python, prefira:

```bash
python -m pip install nome-do-pacote
```

O uso de `python -m pip` reduz o risco de instalar o pacote em um Python diferente daquele usado pelo kernel.

## Licenca e finalidade

Este repositorio reune material didatico, exemplos de aula e exercicios. Os comandos de instalacao podem exigir ajustes conforme a distribuicao Linux, a versao do JDK e os kernels disponiveis no sistema.