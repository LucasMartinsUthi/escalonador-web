let len = dados.length,
        elementos_len = {};
        elementos_fim = {};
        elementos_inicio = {};
        pattern = ["#3366cc", "#dc3912", "#ff9900", "#109618", "#990099", "#0099c6", "#dd4477", "#66aa00", "#b82e2e", "#316395", "#3366cc", "#994499", "#22aa99", "#aaaa11", "#6633cc", "#e67300", "#8b0707", "#651067", "#329262", "#5574a6", "#3b3eac", "#b77322", "#16d620", "#b91383", "#f4359e", "#9c5935", "#a9c413", "#2a778d", "#668d1c", "#bea413", "#0c5922", "#743411"];
        pattern_order = [],
        dados_chart = [];

Simulador = {
    time: 0,
    loop: null,
    play:() => {
        this.time = 0;
        elementos_fim = {}
        elementos_inicio = {}
        Simulador.pause();
        this.loop = setInterval(() => {
            Simulador.forward();
        }, 500);
    },
    pause:()=>{
        clearInterval(this.loop);
    },
    backward: () => {
        if(this.time > 0)
            this.time --;
        simulador(this.time);
    },
    forward: () => {
        if(this.time < dados.length)
            this.time ++;
        simulador(this.time);

        if(this.time == dados.length)
            Simulador.pause();
    },
    eventos: () => {
        $(".play").click(() => {
            Simulador.play();
        });

        $(".pause").click(() => {
            Simulador.pause();
        });

        $(".backward").click(() => {
            Simulador.backward();
        });

        $(".forward").click(() => {
            Simulador.forward();
        })
    }
};

simulador = (time) => {
    if(!dados)
        return false;

    let ret = {},
        dados_slice = dados.slice(0, time);

    $("#view, table tbody").html("");

    dados_slice.forEach((e) => {
        if(!Object.keys(ret).includes(e)){
            ret[e] = elementos_len[e] - dados_slice.filter((x) => x==e).length;
            if(!elementos_inicio[e])
                elementos_inicio[e] = time;    
        }
        
        if(ret[e] == 0 && !elementos_fim[e])
            elementos_fim[e] = time;

        let color = pattern_order.indexOf(String(e)) % 31;
        $("#view").append("<div class='col-1 element' style='background: "+pattern[color]+"; border: 1px solid "+shadeColor(pattern[color], -20)+"'>"+e+"</div>")
    });

    $(".badge").text(dados_slice.length);
    
    
    Object.keys(ret).forEach((e)=>{
        let fim = (elementos_fim[e])? elementos_fim[e] : "#",
            inicio = (elementos_inicio[e])? elementos_inicio[e] : "#";

        $('table tbody').append("<tr>"+
                "<td>"+e+"</td>"+
                "<td>"+ret[e]+"</td>"+
                "<td>"+inicio+"</td>"+
                "<td>"+fim+"</td>"+
            "</tr>"
        )
    });

    drawChart(time)

    return ret;
}

shadeColor = (color, percent) => {
    let R = parseInt(color.substring(1,3),16),
        G = parseInt(color.substring(3,5),16),
        B = parseInt(color.substring(5,7),16);

    R = parseInt(R * (100 + percent) / 100);
    G = parseInt(G * (100 + percent) / 100);
    B = parseInt(B * (100 + percent) / 100);

    R = (R<255)?R:255;  
    G = (G<255)?G:255;  
    B = (B<255)?B:255;  

    let RR = ((R.toString(16).length==1)?"0"+R.toString(16):R.toString(16)),
        GG = ((G.toString(16).length==1)?"0"+G.toString(16):G.toString(16)),
        BB = ((B.toString(16).length==1)?"0"+B.toString(16):B.toString(16));

    return "#"+RR+GG+BB;
}

drawChart = (time = dados.length) => {
    try {
        var data = google.visualization.arrayToDataTable(dados_chart.slice(0, time + 1));
     }
     catch (e) {
         return false;
     }

    var options = {
        title: 'Dados da performance',
        legend: { position: 'top' },
        vAxis: { title: 'Porcentagem'},
        hAxis: { title: 'Clocks'}
    };

    var chart = new google.visualization.LineChart(document.getElementById('chart'));
    chart.draw(data, options);
}

$(() => {
    if(dados){
        dados.pop(dados.length - 1)

        dados.forEach((e, i) => {
            if(!Object.keys(elementos_len).includes(e)){
                elementos_len[e] = dados.filter((x) => x == e).length
                pattern_order.push(e)
                if(!elementos_inicio[e])
                    elementos_inicio[e] = i+1; 
            }

            if(elementos_len[e] - dados.slice(0,i+1).filter((x) => x==e).length ==0 && !elementos_fim[e])
                elementos_fim[e] = i+1;
            
            let color = pattern_order.indexOf(String(e)) % 31;
            $("#view").append("<div class='col-1 element' style='background: "+pattern[color]+"; border: 1px solid "+shadeColor(pattern[color], -20)+"'>"+e+"</div>")
        });

        $(".badge").text(dados.length);

        dados_chart = [Object.keys(elementos_len)];
        dados_chart[0].unshift("Clocks")

        dados.forEach((e, i) => {
            dados_chart.push(
                dados_chart[0].map((a,j) => {
                    if(a == "Clocks")
                        return i+1

                    if(dados[i] == a && i == 0)
                        return 1/elementos_len[a]*100
                    else if(i == 0)
                        return 0
                    
                    valor_anterior = dados_chart[i][j]
                    
                    if(dados[i] == a){
                        valor_anterior += 1/elementos_len[a]*100
                    }

                    return valor_anterior
                })
            );
        });

        Simulador.eventos();

        // Charts
        google.charts.load('current', {'packages':['corechart']});
        google.charts.setOnLoadCallback(drawChart);

        simulador(dados.length)
    }

    // Eventos
    $('.escalonador-btn').click((e)=>{
        $('#escalonador-form').val(e.target.value)
        $('form').submit();
    })
})