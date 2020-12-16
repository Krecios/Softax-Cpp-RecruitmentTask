# Softax-Cpp-RecruitmentTask

W tym repozytorium znajduje się rozwiązanie zadania rekrutacyjnego na stanowisko Junior Backend Developer wykonane przez Filipa Kwiatkowskiego.

Zadanie to jest podzielone na 3 częśći, z których każda zostanie omówiona we własnym podpunkcie.

### 1. Obliczanie metryki

Program do obliczania metryki to `softax.cpp`. Jest to prosty algorytm który przyjmuję nazwę pliku wejściowego w wierszu poleceń i kompiluje się komendą `$ g++ softax.cpp -o metric.o`, a uruchamia `$./metric.o`. Do tej części projektu użyto 2 bibliotek nagłówkowych `nlohmann/json` do parsowania pliku wejściowego oraz `picosha2` do obliczania sha256.

### 2. Usługa REST

Program który wystawia obliczanie metryki na niewielki serwer to `server.cpp`. Używa on biblioteki nagłówkowej `httplib` by utworzyć stronę na adresie `localhost:9000`. Program kompiluje się komendą `$ make` lub `$ g++ -pthread server.cpp -o softax.o`, a uruchamia `$ ./softax.o`. Server ten obsługuje POST na adres `localhost:9000/`, gdzie otrzymuje dane w formacie json, generuje metrykę i sprawdza poprawność metryki przy pomocy `verify.py`. Przykładowy POST na ten adres ma formę: `$ curl -v -X POST -H "Content-Type: application/json" -d @test_file.json $ADDR:9000`, gdzie test_file.json to plik json zgodny z standardem podanym w treści zadania, a $ADDR to zmienna shell'owa, która w tym wypadku powinna zostać ustawiona na localhost.

### 3. Dockerfile

Dockerfile znajdujący się w folderze z resztą plików tworzy obraz Ubuntu 18.04 przystosowany do obsługi serwera. Obraz ten można zbudować poprzez komendę `$ sudo docker build --pull --rm -f "Dockerfile" -t softaxcpp:latest "."`. Z tego obrazu można uruchomić kontener komendą `$ sudo docker run --publish 9000:9000 --detach --name stcpp softaxcpp:latest`. Kontener ten posiada otwarty i zmapowany port 9000. Aby wysłać plik json na ten serwer należy ponownie użyć komendy `$ curl -v -X POST -H "Content-Type: application/json" -d @test_file.json $ADDR:9000` z tymi samymi zastrzeżeniami co w wypadku serwera poza kontenerem.
