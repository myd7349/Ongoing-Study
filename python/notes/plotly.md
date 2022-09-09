[3D Scatter Plots in Python](https://plotly.com/python/3d-scatter-plots/)

```
import plotly.express as px
df = px.data.iris()
fig = px.scatter_3d(df, x='sepal_length', y='sepal_width', z='petal_width',
              color='species')
fig.show()
```

