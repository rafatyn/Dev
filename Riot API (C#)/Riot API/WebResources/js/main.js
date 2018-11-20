$(document).ready(function () {   

    console.log("window width: " + $(window).width());
    console.log("window height: " + $(window).height());
    console.log("body width: " + $('body').width());
    console.log("body height: " + $('body').height());
    console.log("html width: " + $('html').width());
    console.log("html height: " + $('html').height());
    console.log("document width: " + $(document).width());
    console.log("document height: " + $(document).height());
    console.log("game width: " + $('#current-game-info').width());
    console.log("game height: " + $('#current-game-info').height());

    (async function () {
        await CefSharp.BindObjectAsync("UIHandler", "UIHandler");
        console.log(Object.getOwnPropertyNames(window.UIHandler));
    })();

    $(window).on('resize', function () {
        console.log($('#searchSection').outerHeight(true));
        $('#current-game-info').css("height", ($(window).height() - $('#searchSection').outerHeight(true) - ($(window).height() * 0.01)) + "px");
        $('#counter').css("width", $('#counter').css("height"));
    });

    $('.search-button').on('click', function () {
        window.UIHandler.searchSelected($('.summoner-name-input').val());
        //configureCanvas();
    });

    $('.summoner-name-input').on('keypress', function (e) {
        if (e.keyCode == 13)
            $('.search-button').trigger('click');
    });
    
    $(window).trigger('resize');
    
    function progressSim() {
        for (var i = 0; i < window.canvas.length; i++) {
            var left = $(window.canvas[i]).attr('attr-timeLeft');
            if (left >= 0) {
                var ctx = window.canvas[i].getContext('2d');
                var cw = ctx.canvas.width;
                var ch = ctx.canvas.height;
                var total = $(canvas[i]).attr('attr-totalTime');
                var diff = (((total - left) / total) * Math.PI * 2 * 10).toFixed(2);
                ctx.clearRect(0, 0, cw, ch);
                ctx.lineWidth = ch / 2;
                ctx.strokeStyle = 'rgba(90, 90, 90, 0.8)';
                ctx.beginPath();
                ctx.arc(cw / 2, ch / 2, ch / 4, 4.72, diff / 10 + 4.72, true);
                ctx.stroke();
                ctx.strokeStyle = 'rgb(0, 0, 0)';
                ctx.fillStyle = 'rgb(255, 255, 255)';
                ctx.textAlign = 'center';
                ctx.fillText(left + 's', cw / 2, ch / 2 + 14, cw);
                ctx.lineWidth = 3;
                ctx.strokeText(left + 's', cw / 2, ch / 2 + 14);
                ctx.closePath();
                $(window.canvas[i]).attr('attr-timeLeft', left - 1);
            } else {
                var ctx = window.canvas[i].getContext('2d');
                var cw = ctx.canvas.width;
                var ch = ctx.canvas.height;
                ctx.clearRect(0, 0, cw, ch);
                window.canvas.slice(i, 1);
            }
        }
    }

    window.configureCanvas = function () {
        window.canvas = $('.timer-canvas');
        for (var i = 0; i < window.canvas.length; i++) {
            var ctx = window.canvas[i].getContext('2d');
            ctx.font = "bold 35px Arial";
        }

        progressSim();
        var sim = setInterval(progressSim, 1000);

        // Working version, single counter
        //var ctx = document.getElementById('counter').getContext('2d');
        //ctx.font = "bold 35px Arial";
        //var al = 0;
        //var start = 4.72;
        //var cw = ctx.canvas.width;
        //var ch = ctx.canvas.height;
        //var diff;
        //function progressSim() {
        //    diff = ((al / 100) * Math.PI * 2 * 10).toFixed(2);
        //    ctx.clearRect(0, 0, cw, ch);
        //    ctx.lineWidth = ch / 2;
        //    ctx.strokeStyle = 'rgb(255, 255, 255)';
        //    ctx.fillStyle = 'rgb(255, 255, 255)';
        //    ctx.textAlign = 'center';
        //    ctx.fillText(al + '%', cw / 2, ch / 2 + 14, cw);
        //    ctx.strokeStyle = 'rgba(110, 110, 110, 0.8)';
        //    ctx.beginPath();
        //    ctx.arc(cw / 2, ch / 2, ch / 4, start, diff / 10 + start, true);
        //    ctx.stroke();
        //    if (al >= 100) {
        //        clearTimeout(sim);
        //    }
        //    al++;
        //}
        //var sim = setInterval(progressSim, 350);
    };
});