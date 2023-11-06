# Google’s PageRank

O objetivo deste trabalho é aplicar o conceito de Tabela de Símbolos para o desenvolvimento de uma mini máquina de busca. O algorítimo utilizado é o PageRank, desenvolvido pelo Google para a primeira versão de sua máquina de busca.

<p align="center">
  <img src="https://github.com/waldyr/Sublime-Installer/blob/master/sublime_text.png?raw=true" alt="page rank schema"/>
</p>

Quando um usuário digita um termo em uma máquina de busca, há interesse não apenas que os resultados obtidos sejam relevantes, mas também que os mais relevantes sejam apresentados primeiro. Em outras palavras, dadas as páginas que contêm o termo buscado (ou conteúdo relevante aos termos buscados), em que ordem essas páginas devem ser apresentadas pela máquina de busca?
Nos anos 90, havia um interesse muito grande em resolver esse problema, sendo que várias abordagens foram experimentadas. Por volta de 1997/1998, os criadores do Google propuseram o PageRank, método que serve como base para novos algoritmos até os dias de hoje. O princípio básico do PageRank consiste no fato de que a importância de uma página Web não depende de seu conteúdo, autor, quem a possui, onde está hospedada, etc., mas sim de quão influente essa página é sobre outras páginas da Web. Nesse contexto, a influência de uma página sobre outra é dada pela existência de um link entre elas.


# Setup

* Certifique-se que tenha ````GCC ^11.3``` e ````Makefile ^4.0``` instalados.

* Clone este repositório localmente:

```bash
git clone https://github.com/MateusSartorio/googles-page-rank.git
```

* Para compilar e em seguida rodar o programa, execute os comandos:

```
make
make run
```

* Agora basta digitar as palavras chaves que quer pesquisar.

## Licença:

Copyright Universidade Federal do Espirito Santo (Ufes)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

This program is released under license GNU GPL v3+ license.

## Suporte
Por favor reporte qualquer problema com o programa em https://github.com/MateusSartorio/googles-page-rank.
