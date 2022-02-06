CFLAGS= -Wall -Werror

#regra padrão, make executa regra padrão
all: cliente

#regra cliente declara as dependencias e as executa
#se algum desses arquivos são alterados, compila-se novamente
cliente: cliente.c arvore.o fila.o lista_circular.o
	gcc $^ -o $@
# gcc cliente.c lkdlist.o -o cliente

#regra generica
%.o: %.c %.h
	gcc $(CFLAGS) -c $<

clean:
	rm -rf *.o cliente

