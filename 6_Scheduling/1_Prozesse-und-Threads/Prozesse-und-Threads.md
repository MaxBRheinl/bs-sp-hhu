# Aufgabe 6.1: Prozesse und Threads

Aufgabenstellung:

Die meisten Betriebssysteme ermöglichen nebenläufige Aktivitäten auf Basis von Prozessen beziehungsweise Threads.

- Erläutern Sie die Beziehung zwischen den Begriffen Thread und Prozess.
    
    > Antwort:
    > 
    > 
    > Sowohl Threads als auch Prozesse führen Programmanweisungen aus. 
    > 
    > Ein Prozess ist dabei allerdings eine eigenständige Instanz eines Programms mit eigenem Speicherbereich und Ressourcen. Jeder Prozess läuft unabhängig von anderen Prozessen.
    > 
    > Ein Thread hingegen ist eine Unterinstanz eines anderen Prozesses. Mehrere Threads innerhalb desselben Prozesses teilen sich den gleichen Speicherbereich (Adressraum) und andere Ressourcen wie offene Dateien oder Netzwerkverbindungen.
    > 
    
- Die nebenläufige Ausführung von Threads kann dazu führen, dass sich verschiedene Threads gegenseitig beeinflussen. Finden Sie Beispiele für die negative Beeinflussung zwischen Threads.
    
    > Antwort:
    > 
    > 
    > (Race-Conditions)
    > 
    > Es kann zu Inkonsitenzen kommen wenn zwei Threads zeitgleich Werte an Adressen schreiben, die sie beide nutzen.
    > 
    > (Deadlocks)
    > 
    > Außerdem könnten zwei Threads sich gegenseitig blockieren. Indem zum Beispiel ein Thread eine Ressource belegt und auf die Freigabe einer anderen wartet, die wiederum durch einen Thread blockiert wird, der auf die Freigabe der Ressource, die der erste Thread blockiert, wartet. So entsteht ein Kreis von Abhänigkeiten.
    > 
    > (Konvoi-Effekt)
    > 
    > Zusätzlich kann der Konvoi-Effekt beim FCFS-Scheduling mit kooperativem Multitasking auftreten. Wenn ein Thread die CPU für eine lange Zeit blockiert, müssen andere Threads warten, bis dieser fertig ist, selbst wenn sie nur kurze Berechnungen durchführen müssten.
    > 

- In welchen Fällen ist es sinnvoll, nebenläufige Programmteile mit Hilfe von Threads anstatt von Prozessen zu implementieren?
    
    > Antwort:
    > 
    > 
    > (Ressourcensparsamkeit)
    > 
    > Threads bieten sich immer dort an, wenn Ressourcensparsam berechnet werden soll.
    > 
    >  
    > 
    > (Echtzeitanwendungen)
    > 
    > Gerade bei Echtzeitanwendungen wie Benutzeroberflächen bietet es sich an Threads zu verwenden. Da bei einem blockierendem I/O die Wartezeit genutzt werden kann.
    > 
    > (gemeinsamer Adressraum)
    > 
    > Sobald Programmteile auf gleiche Speicherdaten zugreifen können sollen oder kein Schutz des Adressraums notwendig ist, bieten sich Threads an.
    > 
    > **Tipp**: Es deutlich kostengünstiger zwischen Threads zu wechsel als zwischen Prozessen zu wechseln, auf Grund des Adressraumwechsels.
