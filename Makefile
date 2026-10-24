CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic
LDFLAGS =

# Diretórios
BIN_DIR = bin
OBJ_DIR = obj
DOC_DIR = Documentacao
HTML_DIR = $(DOC_DIR)/html

# Arquivos fontes por módulo
SRCS_DOMINIOS = Dominios/dominios.cpp
SRCS_ENTIDADES = Entidades/entidades.cpp
SRCS_REPOSITORIOS = Repositorios/repositorios.cpp
SRCS_SERVICOS = Servicos/controladoras_servico.cpp
SRCS_APRESENTACAO = Apresentacao/apresentacao.cpp
SRCS_MAIN = Main/main.cpp

# Fontes de testes
SRCS_TESTES_DOMINIOS = Testes/testes_dominios.cpp
SRCS_TESTES_ENTIDADES = Testes/testes_entidades.cpp
SRCS_TESTES_UNITARIOS = Testes/testes_unitarios.cpp
SRCS_SMOKE_TEST = Testes/smoke_test_controladoras.cpp

# Binários gerados
TARGET_MAIN = Projeto_TP1
TARGET_DEBUG = $(BIN_DIR)/Debug/Projeto_TP1
TARGET_RELEASE = $(BIN_DIR)/Release/Projeto_TP1
TARGET_SMOKE = $(BIN_DIR)/SmokeTest/SmokeTest
TARGET_UNIT = $(BIN_DIR)/TestesUnitarios/TestesUnitarios

.PHONY: all clean test test_unit test_smoke test_integrated doc zip help

all: dirs $(TARGET_MAIN) $(TARGET_DEBUG) $(TARGET_RELEASE) $(TARGET_SMOKE) $(TARGET_UNIT)

dirs:
	@mkdir -p $(BIN_DIR)/Debug $(BIN_DIR)/Release $(BIN_DIR)/SmokeTest $(BIN_DIR)/TestesUnitarios $(DOC_DIR)

# Executável principal na raiz e alvos Code::Blocks
$(TARGET_MAIN): $(SRCS_DOMINIOS) $(SRCS_ENTIDADES) $(SRCS_REPOSITORIOS) $(SRCS_SERVICOS) $(SRCS_APRESENTACAO) $(SRCS_MAIN)
	$(CXX) $(CXXFLAGS) -O2 $^ -o $@ $(LDFLAGS)

$(TARGET_DEBUG): $(SRCS_DOMINIOS) $(SRCS_ENTIDADES) $(SRCS_REPOSITORIOS) $(SRCS_SERVICOS) $(SRCS_APRESENTACAO) $(SRCS_MAIN)
	$(CXX) $(CXXFLAGS) -g $^ -o $@ $(LDFLAGS)

$(TARGET_RELEASE): $(SRCS_DOMINIOS) $(SRCS_ENTIDADES) $(SRCS_REPOSITORIOS) $(SRCS_SERVICOS) $(SRCS_APRESENTACAO) $(SRCS_MAIN)
	$(CXX) $(CXXFLAGS) -O2 -s $^ -o $@ $(LDFLAGS)

$(TARGET_SMOKE): $(SRCS_DOMINIOS) $(SRCS_ENTIDADES) $(SRCS_REPOSITORIOS) $(SRCS_SERVICOS) $(SRCS_SMOKE_TEST)
	$(CXX) $(CXXFLAGS) -O2 $^ -o $@ $(LDFLAGS)

$(TARGET_UNIT): $(SRCS_DOMINIOS) $(SRCS_ENTIDADES) $(SRCS_TESTES_DOMINIOS) $(SRCS_TESTES_ENTIDADES) $(SRCS_TESTES_UNITARIOS)
	$(CXX) $(CXXFLAGS) -O2 $^ -o $@ $(LDFLAGS)

# Execução dos testes
test: test_unit test_smoke test_integrated
	@echo "\n=============================================="
	@echo " TODOS OS TESTES FORAM EXECUTADOS COM SUCESSO!"
	@echo "=============================================="

test_unit: dirs $(TARGET_UNIT)
	@echo "\n>>> Executando Testes de Unidade (Dominios e Entidades)..."
	./$(TARGET_UNIT)

test_smoke: dirs $(TARGET_SMOKE)
	@echo "\n>>> Executando Teste de Fumaca das Controladoras de Servico..."
	./$(TARGET_SMOKE)

test_integrated: dirs $(TARGET_MAIN)
	@echo "\n>>> Executando Teste de Fumaca Integrado com Roteiro Automatizado..."
	./$(TARGET_MAIN) < Testes/roteiro_teste_fumaca.txt

# Documentação
doc:
	@echo "\n>>> Gerando Documentacao HTML com Doxygen..."
	@if [ -x /tmp/doxygen-1.9.8/bin/doxygen ]; then \
		/tmp/doxygen-1.9.8/bin/doxygen Doxyfile; \
	elif which doxygen > /dev/null 2>&1; then \
		doxygen Doxyfile; \
	else \
		echo "Aviso: doxygen nao encontrado no PATH nem em /tmp."; \
	fi
	@echo "\n>>> Gerando PDF do Modelo de Arquitetura..."
	@libreoffice -env:UserInstallation=file:///tmp/libreoffice_user --headless --convert-to pdf --outdir $(DOC_DIR) $(DOC_DIR)/Modelo_Arquitetura.html >/dev/null 2>&1 || true
	@cp -f $(DOC_DIR)/Modelo_Arquitetura.pdf ./Modelo_Arquitetura.pdf 2>/dev/null || true
	@echo "Documentacao gerada em $(DOC_DIR)/ e Modelo_Arquitetura.pdf"

# Empacotamento para Entrega
zip: all doc test
	@echo "\n>>> Criando pacote ZIP de entrega..."
	@ZIP_NAME="T1-TP1-Arthur-Gabriel-Isabela-Joao.ZIP"; \
	rm -f $$ZIP_NAME; \
	zip -r -q $$ZIP_NAME . -x ".*" ".git/*" "obj/*" "build/*" "/tmp/*"; \
	echo "Arquivo de entrega gerado: $$ZIP_NAME"; \
	unzip -t $$ZIP_NAME >/dev/null && echo "Verificacao de integridade do ZIP: OK!"

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR) $(TARGET_MAIN) $(DOC_DIR)/html *.zip
