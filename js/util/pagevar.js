function pagevars(total_num, pagelen, current_page){
    var init=1;
    var max = total_num;
    current_page = current_page || 1;
    pagelen = pagelen || 7;
    pagelen = (pagelen % 2) ? pagelen : pagelen + 1;
    pageoffset = (pagelen - 1) / 2;
    
    if ( total_num > pagelen )
    {
        if ( current_page <= pageoffset )
        {
          init=1;
          max = pagelen;
        }
        else
        {
          if ( current_page + pageoffset >= total_num + 1 )
          {
            init = total_num - pagelen + 1;
          }
          else
          {
            init = current_page - pageoffset;
            max = current_page + pageoffset;
          }
        }
    }
    
    return {
      init: init,
      max: max
    };  
}