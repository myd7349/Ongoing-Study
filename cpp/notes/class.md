["No appropriate default constructor available"--Why is the default constructor even called?](https://stackoverflow.com/questions/15710125/no-appropriate-default-constructor-available-why-is-the-default-constructor-e)

> ```cpp
> class ProxyPiece
> {
> public:
>     ProxyPiece(CubeGeometry& c);
>     virtual ~ProxyPiece(void);
> private:
>     CubeGeometry cube;
> };
> 
> ProxyPiece::ProxyPiece(CubeGeometry& c)
> {
>     cube=c;
> }
> 
> 
> ProxyPiece::~ProxyPiece(void)
> {
> }
> ```
>
> Your default constructor is implicitly called here:
>
> ```cpp
> ProxyPiece::ProxyPiece(CubeGeometry& c)
> {
>     cube=c;
> }
> ```
>
> You want
>
> ```cpp
> ProxyPiece::ProxyPiece(CubeGeometry& c)
>    :cube(c)
> {
>     
> }
> ```
>
> Otherwise your ctor is equivalent to
>
> ```cpp
> ProxyPiece::ProxyPiece(CubeGeometry& c)
>     :cube() //default ctor called here!
> {
>     cube.operator=(c); //a function call on an already initialized object
> }
> ```

