# **Roteiro de execução — Cadastro, autenticação e criação de projeto**



##### testaremos esta sequência:

##### 1\. Criar uma conta de gestor.

##### 2\. Encerrar completamente o programa.

##### 3\. Abrir novamente e autenticar a conta.

##### 4\. Entrar no menu de projetos.

##### 5\. Criar um projeto.

##### 6\. Confirmar que o projeto foi criado e que o usuário autenticado se tornou seu gestor.

##### 7\. excluir Projeto e confirmar se foi excluído







###### **Inicialmente, vamos realizar o cadastro de um usuário com perfil de gestor. Após concluir o cadastro, vamos encerrar completamente o sistema e executá-lo novamente para verificar a persistência das informações no banco de dados SQLite.**

###### 

###### **Em seguida, vamos autenticar o usuário cadastrado e verificar se o sistema reconhece corretamente seu papel de gestor.**

###### 

###### **Após a autenticação, acessaremos o menu de projetos e realizaremos o cadastro de um novo projeto, informando identificador, nome, descrição e período de execução.**

###### 

###### **Por fim, vamos consultar o projeto recém-criado para verificar se todas as informações foram armazenadas corretamente.**



&#x20;./Projeto\_TP1.exe   //inicia o sistema de software

###### 

###### === Sistema Kanban ===

###### 1 - Entrar

###### 2 - Criar conta

###### 0 - Sair

###### 

###### \## 1. Criar uma conta de gestor

###### 

###### Digitaremos: 2

###### 

###### | Campo | Entrada |

###### |---|---|

###### | Email | gestor.01@exemplo.com |

###### | Nome | Primeiro Gestor |

###### | Senha | a1b2C |

###### | Papel | GESTOR |



###### Resultado esperado: ```text\[OK] Conta criada.```

###### 

###### Pressione Enter se o programa solicitar continuação.

###### 

###### 

###### \## 2. Sair completamente do programa

###### 

###### Você retornará à tela inicial:

###### 

###### === Sistema Kanban ===

###### 1 - Entrar

###### 2 - Criar conta

###### 0 - Sair

###### 

###### 

###### Digitaremos: 0

###### 

###### Resultado esperado:

###### 

###### ```text Ate logo. ```

###### 

###### \## 3. Abrir novamente o programa

###### 

###### No terminal do VSCode, executaremos novamente:

###### 

###### ```bash./Projeto\_TP1```

###### 

###### A tela inicial deverá aparecer novamente.

###### 

###### Digite:1

###### 

###### O programa solicitará:

###### 

###### 

###### Entrar ---

###### Email:

###### Senha:

###### 

###### 

###### Informe:

###### 

###### 

###### Email: gestor.01@exemplo.com

###### Senha: a1b2C

###### 

###### 

###### Resultado esperado:

###### 

###### 

###### \[OK] Autenticado como gestor.01@exemplo.com.

###### 

###### 

###### A autenticação confirma que os dados cadastrados anteriormente foram preservados.

###### 

###### 

###### \## 4. Acessar o menu de projetos

###### 

###### Depois da autenticação, deverá aparecer:

###### 

###### 

###### === Menu principal (gestor.01@exemplo.com - GESTOR) ===

###### 1 - Pessoas

###### 2 - Projetos

###### 3 - Quadros

###### 0 - Sair da sessao

###### 

###### 

###### Digite: 2

###### 

###### O menu de projetos deverá apresentar:

###### 

###### 

###### \--- Projetos ---

###### 1 - Criar

###### 2 - Ler

###### 3 - Atualizar

###### 4 - Excluir

###### 5 - Listar

###### 0 - Voltar

###### 

###### 

###### Digite: 1

###### 

###### 

###### \## 5. Criar o primeiro projeto

###### 

###### O sistema solicitará cinco informações.

###### 

###### Preencheremos exatamente nesta ordem:

###### 

###### //---------Text----------//

###### | Campo solicitado | Valor |

###### |---|---|

###### | Identificador | CIC197 | abc123

###### | Nome | Projeto Kanban | GESTOR

###### | Descrição | Projeto de teste. |

###### | Início | 1-JAN-2026-09:00 |

###### | Término | 2-JAN-2026-17:00 |

###### //---------Text----------//

###### 

###### A sequência de entradas será:

###### 

###### CIC197 || abc123

###### Projeto Kanban || GESTOR

###### Projeto de teste.

###### 1-JAN-2026-09:00

###### 2-JAN-2026-17:00

###### 

###### 

###### Resultado esperado:

###### 

###### //---------Text----------//

###### \[OK] Projeto criado. Voce e o gestor.

###### //---------Text----------//

###### 

###### 

###### \## 6. Confirmar a criação do projeto

###### 

###### Após a criação, pressione Enter se solicitado.

###### 

###### No menu de projetos, digite: 2

###### 

###### Informe: CIC197

###### 

###### 

###### O sistema deverá apresentar os dados cadastrados:

###### 

###### //---------Text----------//

###### Identificador: CIC197 || abc123

###### Nome: Projeto Kanban || GESTOR

###### Descricao: Projeto de teste.

###### Inicio: 1-JAN-2026-09:00

###### Termino: 2-JAN-2026-17:00

###### //---------Text----------//

###### 

###### Confira se os dados estão corretos.

###### 

###### \## 8. Encerrar a demonstração desta etapa

###### 

###### Digite: 0

###### 

###### Para voltar ao menu principal.

###### 

###### Depois: 0

###### 

###### Para encerrar a sessão.

###### 

###### O sistema deverá apresentar:

###### 

###### //---------Text----------//

###### Sessão encerrada.

###### //---------Text----------//

###### 

###### Ao voltar à tela inicial, digite:0

###### 

###### Resultado esperado:

###### 

###### //---------Text----------//

###### Ate logo.

###### //---------Text----------//

