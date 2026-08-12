# Telemetry Node Agent

[![Go Report Card](https://goreportcard.com/badge/github.com/telemetryinc/telemetry-node-agent)](https://goreportcard.com/report/github.com/telemetryinc/telemetry-node-agent)
[![License](https://img.shields.io/badge/License-Apache_2.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

The agent gathers metrics related to a node and the containers running on it, and it exposes them in the Prometheus format.

It uses eBPF to track container related events such as TCP connects, so the minimum supported Linux kernel version is 5.1.

## Features

### TCP connection tracing

To provide visibility into the relationships between services, the agent traces containers TCP events, such as *connect()* and *listen()*.

Exported metrics are useful for:
* Obtaining an actual map of inter-service communications. It doesn't require integration of distributed tracing frameworks into your code.
* Detecting connections errors from one service to another.
* Measuring network latency between containers, nodes and availability zones.

### Log patterns extraction

Log management is usually quite expensive. In most cases, you do not need to analyze each event individually.
It is enough to extract recurring patterns and the number of the related events.

This approach drastically reduces the amount of data required for express log analysis.

The agent discovers container logs and parses them right on the node.

At the moment the following sources are supported:
* Direct logging to files in */var/log/*
* Journald
* Dockerd (JSON file driver)
* Containerd (CRI logs)

### Delay accounting

[Delay accounting](https://www.kernel.org/doc/html/latest/accounting/delay-accounting.html) allows engineers to accurately
identify situations where a container is experiencing a lack of CPU time or waiting for I/O.

The agent gathers per-process counters through [Netlink](https://man7.org/linux/man-pages/man7/netlink.7.html) and aggregates them into per-container metrics:
* `container_resources_cpu_delay_seconds_total`
* `container_resources_disk_delay_seconds_total`

### Out-of-memory events tracing

The `container_oom_kills_total` metric shows that a container has been terminated by the OOM killer.

### Instance meta information

If a node is a cloud instance, the agent identifies a cloud provider and collects additional information using the related metadata services.

Supported cloud providers: [AWS](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/instancedata-data-retrieval.html), [GCP](https://cloud.google.com/compute/docs/metadata/overview), [Azure](https://docs.microsoft.com/en-us/azure/virtual-machines/linux/instance-metadata-service?tabs=linux), [Hetzner](https://docs.hetzner.cloud/#server-metadata)

Collected info:
* AccountID
* InstanceID
* Instance/machine type
* Region
* AvailabilityZone
* AvailabilityZoneId (AWS only)
* LifeCycle: on-demand/spot (AWS and GCP only)
* Private & Public IP addresses

## Installation

<!-- TODO: replace with the real Telemetry docs URL once available -->
Follow the Telemetry documentation at https://yourbrand.example.com/docs

## Metrics

<!-- TODO: replace with the real Telemetry docs URL once available -->
The collected metrics are described at https://yourbrand.example.com/docs/metrics/node-agent

## Contributing

To start contributing, check out our [Contributing Guide](https://github.com/telemetryinc/telemetry-node-agent/blob/main/CONTRIBUTING.md).

## License

Telemetry Node Agent is licensed under the [Apache License, Version 2.0](https://github.com/telemetryinc/telemetry-node-agent/blob/main/LICENSE).
See [NOTICE.md](NOTICE.md) for third-party attribution.

The BPF code is licensed under the General Public License, Version 2.0.
