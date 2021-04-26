# ML-projects

Collection of machine learning projects. Each project is within its own sub-folder inside `projects`.

## Jupter Deployment

All the notebooks can be accessed by deploying a jupyter-notebook server. The recomended way to deploy the server is to use the provided `docker-compse.yaml` file.
```bash
  $ docker-compose up -d
```
When the deployment is done, the URL for the jupyter server can be obtained from the logs. To do so just run: 
```bash
  $ docker-compose logs
```
The URL would be of the form `http://localhost:8888/lab?token=<token>`.

To bring down the server run the following command:
```bash
  $ docker-compose down
```

