<?php
    exec("./escalonador", $out);
    $dados = json_decode($out[0]);
?>


<html>
    <head>
        <title>Escalonador</title>
        <meta charset="UTF-8" />
        <link rel="stylesheet" href="style.css">
        <script src="main.js"></script>
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.0/jquery.min.js"></script>
        <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">
    </head>
    <body>
        <div class="container">
            <div class="row">
                <?php
                    foreach($dados as $d){
                        echo "<div class='col {$d}'>{$d}</div>";
                    }
                ?>
            </div>
        </div>
    </body>
</html>
</html>