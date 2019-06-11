<html>
    <head>
        <title>Escalonador</title>
        <meta charset="UTF-8" />
        <link rel="stylesheet" href="style.css">
        <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">
        <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
        <script src="https://kit.fontawesome.com/44e1483c1e.js"></script>
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.0/jquery.min.js"></script>
        <script> let dados = 
            <?php 
                if(isset($_GET["escalonador"]))
                    echo exec("./simulador/simulator ./simulador/entrada2.txt {$_GET["escalonador"]} 2", $out);
                else
                    echo "''"; 
            ?>;
        </script>
        <script src="main.js"></script>
    </head>
    <body>
        <div class="container">
            <div class="row mt-4">
                <form action="" methos="get"><input type="hidden" id="escalonador-form" name="escalonador"></form>
                <button type="button" class="btn btn-success mr-4 escalonador-btn" value="FCFS">FCFS</button> 
                <button type="button" class="btn btn-warning mr-4 escalonador-btn" value="SJF">SJF</button>
                <button type="button" class="btn btn-primary mr-4 escalonador-btn" value="RR">RR</button>
            </div>
            <?php 
                $titulo = (isset($_GET["escalonador"]) ? $_GET["escalonador"] : "Escalonador");

                echo "<div class='row my-4'>
                    <h1>{$titulo}</h1>
                </div>"; 
            ?>
            <div id="view" class="row mb-5 text-center">
            </div>
            <div class="row">
                <div class="col-8 simulation">
                    <button type="button" class="btn btn-light play"><i class="fas fa-play"></i></button>
                    <button type="button" class="btn btn-light pause"><i class="fas fa-pause"></i></button>
                    <button type="button" class="btn btn-light backward"><i class="fas fa-backward"></i></button>
                    <button type="button" class="btn btn-light forward"><i class="fas fa-forward"></i></button>
                </div>
                <div class="col-4">
                    <h4 class="d-flex justify-content-between align-items-center mb-3">
                        <span>Processos:</span>
                        <span class="badge badge-dark badge-pill">0</span>
                    </h4>
                </div>
            </div>
            <div class="row mt-3">
                <table class="table table-striped">
                    <thead>
                        <tr>
                            <th scope="col">Processos</th>
                            <th scope="col">Restantes</th>
                            <th scope="col">Inicio</th>
                            <th scope="col">Fim</th>
                        </tr>
                    </thead>
                    <tbody>
                    </tbody>
                </table>
            </div>
            <div class="row mt-3">
                <div class="col-6" id="chart"></div>
            </div>
        </div>
    </body>
</html>
</html>